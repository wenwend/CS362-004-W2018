



import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!



public class UrlValidatorTest extends TestCase {
   
   /*this is for partition test usage*/
   String[] validAuthority = new String[]{"www.google.com","go.au","255.255.255.255","255.com"};
   String[] invalidAuthority = new String[]{"","1.2.3.4.5","go.a",".aaa"};
   String[] validScheme = new String[]{"http://","h3t://","ftp://","file://"};
   String[] invalidScheme = new String[]{"://","http:","http:/",""}; //be aware "" empty scheme is considered invalid
   String[] validPort= new String[]{":80",":65535","",":1024"};
   String[] invalidPort = new String[]{":-1",":65636",":65a",":eee"};
   String[] validPath= new String[]{"/test1","/$23","/test1/file"};
   String[] invalidPath=new String[]{"/../","/..","/test1//file1"};
   String[] validQuery=new String[]{"","?action=view","?q=dmv"};
   
   public UrlValidatorTest(String testName) {
      super(testName);
   } 
   
   public void testIsValid()
   {
      System.out.println("Programming test starting here...");
      UrlValidator urlVal = new UrlValidator(null,null, UrlValidator.ALLOW_ALL_SCHEMES);
      String[][] RandomList={validScheme,invalidScheme,validAuthority,invalidAuthority,validPort,invalidPort,validPath,invalidPath,validQuery};
      String url;
      Boolean actual,expected;
      int i,j,l,k,m,n,count=0,bugs;
      String[] invalidURL = new String[100];
      //a simply random test with only two component, do it 10 times
      do{
         
         do{
            i=genRandom(9);
            j=genRandom(9);
         }while(i==j || i==j+1 || i==j-1 || i>j);
         
      System.out.printf(i+" "+j+'\n');
    
      if(i==0 && j==2)
         expected=true;//only valid scheme and valid authority will return a true.
      else
         expected=false;
      
      for(String p: RandomList[i])
         for(String q: RandomList[j]){
            url=p+q;
            actual=urlVal.isValid(url);
            System.out.printf(url+"is ");
            if(expected==actual)
               System.out.println(actual+": Pass!");
            else
               System.out.println(actual+": Fail!");
         }
      count++;
      }while(count<10);
      
      
      count=0;// loop counting
      bugs=0; // bug counting
      //a better random test.
      do{
         
         i=genRandom(4);
         j=genRandom(4);
         l=genRandom(4);
         k=genRandom(3);
         m=genRandom(3);
         //invalid
         url=RandomList[1][i]+RandomList[2][j]+RandomList[4][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         //invalid
         url=RandomList[1][i]+RandomList[3][j]+RandomList[4][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         //invalid
         url=RandomList[1][i]+RandomList[2][j]+RandomList[5][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         //invalid
         url=RandomList[1][i]+RandomList[2][j]+RandomList[4][l]+RandomList[7][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         
         //invalid
         url=RandomList[1][i]+RandomList[3][j]+RandomList[4][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         //invalid
         url=RandomList[1][i]+RandomList[2][j]+RandomList[5][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
       //invalid
         url=RandomList[1][i]+RandomList[2][j]+RandomList[4][l]+RandomList[7][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         //invalid
         url=RandomList[1][i]+RandomList[3][j]+RandomList[5][l]+RandomList[7][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=false){
            invalidURL[bugs]=url;
            bugs++;
         }
         
         //invalid
         url=RandomList[0][i]+RandomList[2][j]+RandomList[4][l]+RandomList[6][k]+RandomList[8][m];
         actual=urlVal.isValid(url);
         if(actual!=true){
            invalidURL[bugs]=url;
            bugs++;
         }
        count++;
      }while(count<10);
      
      if(bugs!=0){
         System.out.printf("Total find out %d bugs.\n INVALID URL are:\n",bugs);
         for(String o:invalidURL)
            if(o!=null)
               System.out.println(o);
      }
      else
         System.out.println("ZERO bugs found!");

   }
   public int genRandom(int n){
      //Random rand = new Random();
      Random rand = new Random(System.currentTimeMillis());
      
      return (int)rand.nextInt(n);
   }
   
   
}
