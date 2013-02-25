
import java.io.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.util.zip.CRC32;
import java.util.zip.Deflater;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;


public class Jpigz {
	
	public static final int BLOCK_SIZE = 128*1024; //size of compression block
	public static final int DICTIONARY_SIZE = 32*1024; //size of priming dictionary block
	public static final int HEADER_LENGTH =  10;
	public static final int FOOTER_LENGTH =   8;
	
	public static FileChannel infoWriter = new FileOutputStream(FileDescriptor.out).getChannel();
	public static FileOutputStream dataWriter = new FileOutputStream(FileDescriptor.out);

	public static void headerWriter() 
	{
		try
		{
			ByteBuffer header = ByteBuffer.allocate(HEADER_LENGTH);
			header.order(ByteOrder.LITTLE_ENDIAN);
			header.putInt(0x00088B1F).putInt((int)(System.currentTimeMillis()/1000L)).putShort((short)0xFF00);
			header.flip();
			infoWriter.write(header);
		}
		catch (IOException e)
		{
			System.err.println("error");
		}
	}

	public static void footerWriter(int value, int length)
	{
		try
		{
			ByteBuffer footer = ByteBuffer.allocate(FOOTER_LENGTH);
			footer.order(ByteOrder.LITTLE_ENDIAN);
			footer.putInt(value).putInt((int)(length % Math.pow(2,32)));
			footer.flip();
			infoWriter.write(footer);
		}
		catch (IOException e)
		{
			System.err.println("error");
		}
	}


	public static void main(String[] args) 
    { try{
		boolean isIndependent = false;
		int numProcessors = Runtime.getRuntime().availableProcessors();

		//parse the command line arguments
		for (int i = 0; i < args.length; i++)
		{
			if (args[i].equals("-i")) //want to set independent
			{
				isIndependent = true;
			}
			else if (args[i].equals( "-p")) //want to set number of processors
			{
				try 
				{
					i++;
					int newNum = Integer.parseInt(args[i]);
					if (newNum > numProcessors) //can't use that many
					{	
						System.err.println("System does not have that many processors.");
					}
					else // all good
					{
						numProcessors = Integer.parseInt(args[i]);
					}
					continue;
				}
				catch (ArrayIndexOutOfBoundsException e)
				{
					System.err.println("Please specify the number of processors.");
					System.exit(1);
				}
				catch (NumberFormatException e)
				{
					System.err.println("Please enter an integer number of processors.");
					System.exit(1);
				}
			}
			else //invalid argument
			{
				System.err.println("Invalid arguments.");
				System.err.println("-i: build with independent dictionary");
				System.err.println("-p (integer): build with specified number of processors");
				System.exit(1);
			}
		}

		CRC32 myCRC = new CRC32();
		myCRC.reset();

		//initialize an executor with the number of processors we specified
		ExecutorService executor = Executors.newFixedThreadPool(numProcessors);
		List<Future<byte[]>> list = new ArrayList<Future<byte[]>>();


		//buffered reader for input. buffer size 128kb
		BufferedInputStream bi = new BufferedInputStream(System.in);
		byte[] byte_buf = new byte[BLOCK_SIZE];
		byte[] dict = new byte[DICTIONARY_SIZE];
		int total_size = 0; //holds the size of input file for CRC later

		int c = bi.read(byte_buf, 0, BLOCK_SIZE);  //initialize byte counter
		for (;
			 c == BLOCK_SIZE; // returns number of blocks read; when less than this, stop bc end
			 c = bi.read(byte_buf, 0, BLOCK_SIZE))
		{
			myCRC.update(byte_buf, 0, c); //updating the crc with our values
			total_size += byte_buf.length;


			Callable<byte[]> worker = new Deflater_Thread(byte_buf,dict);
			Future<byte[]> submit = executor.submit(worker);
			list.add(submit);
			
			//"prime" the dictionary for the next block
			if (!isIndependent)
			{
				dict = new byte[DICTIONARY_SIZE];
				dict = Arrays.copyOfRange(byte_buf, BLOCK_SIZE-DICTIONARY_SIZE, BLOCK_SIZE);
			}
			byte_buf = new byte[BLOCK_SIZE];
		}

		if (c > 0)
		{
			//CRC update
			byte[] trimmed_byte_buf = new byte[c];
			System.arraycopy(byte_buf, 0, trimmed_byte_buf, 0, c);
			myCRC.update(trimmed_byte_buf, 0,c);
			total_size += trimmed_byte_buf.length;

			//need to finish the stream with remaining bytes once finished
			Callable<byte[]> end_worker = new Deflater_Thread(trimmed_byte_buf, dict);
			Future<byte[]> end_submit = executor.submit(end_worker);
			list.add(end_submit);
		} 
		executor.shutdown();	
		//now we can retrieve the result from the answer_list
		//The future list is already in order (yay!)
		
		//first the header
		headerWriter();
		
		//next each calculated future (each parsed section, in order)
		for (Future<byte[]> future : list)
		{
			byte[] f = future.get();
			try
			{
				//now attempt to write these bytes to the file
				dataWriter.write(f, 0, f.length);
			}
			catch (IOException e)
			{
			}
		}
		//finally the trailer
		footerWriter((int)myCRC.getValue(), total_size);
		} catch (Exception e) {e.printStackTrace();}
	}
}
