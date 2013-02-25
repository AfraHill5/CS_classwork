
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.util.zip.CRC32;
import java.util.zip.Deflater;
import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.util.concurrent.Callable;
import java.util.Arrays;

public class Deflater_Thread implements Callable<byte[]> 
{
	public static final int BLOCK_SIZE = 128*1024;
    public static final int HEADER_LENGTH = 10;
    public static final int FOOTER_LENGTH = 8;
    public static final int DICTIONARY_SIZE=8;

	public final byte[] inputBytes;
	public final byte[] dict;

	public Deflater_Thread(final byte[] inputBytes, final byte[] dict)
	{
		this.inputBytes = inputBytes;
		this.dict = dict;
	}
    
	public byte[] call()
    {
			Deflater compressor = new Deflater(Deflater.DEFAULT_COMPRESSION, true);
			byte[] buffer = new byte[BLOCK_SIZE];

			
			compressor.setInput(inputBytes);
			if (dict.length > 0)
				compressor.setDictionary(dict); 
			
			int compressedDataLength = 0;
			if (inputBytes.length < BLOCK_SIZE) 
			{//last block in the sequence, so no flush	
				compressor.finish();
				compressedDataLength = compressor.deflate(buffer, 0, buffer.length, Deflater.NO_FLUSH);
			}
			else //sync flush
			{
				compressedDataLength = compressor.deflate(buffer, 0, buffer.length, Deflater.SYNC_FLUSH);
			}
			
			compressor.end();
			//trim the buffer to size
			byte[] sized_buffer = new byte[compressedDataLength];
			sized_buffer = Arrays.copyOf(buffer, compressedDataLength);
			return sized_buffer; 
	}
}

