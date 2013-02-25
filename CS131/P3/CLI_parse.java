public class CLI_parse 
{
    public static void main(String args[])
    {
		boolean isIndependent = false;
		int numProcessors = Runtime.getRuntime().availableProcessors();
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
						System.out.println("System does not have that many processors.");
					}
					else // all good
					{
					numProcessors = Integer.parseInt(args[i]);
					}
					continue;
				}
				catch (ArrayIndexOutOfBoundsException e)
				{
					System.out.println("Please specify the number of processors.");
					System.exit(1);
				}
				catch (NumberFormatException e)
				{
					System.out.println("Please enter an integer number of processors.");
					System.exit(1);
				}
			}
			else //invalid argument
			{
				System.out.println("Invalid arguments.");
				System.out.println("-i: build with independent dictionary");
				System.out.println("-p (integer): build with specified number of processors");
				System.exit(1);
			}
		}
        System.out.println("Is Independent?");
        System.out.println(isIndependent);
        System.out.println("Number of processors?");
        System.out.println(numProcessors);
	}
}
