void draw(){
   const Int_t n=79;
   Int_t z=0,a=0;
   Double_t Z[n],A[n];

   ifstream fin("data.txt");
   int count=0;
   
    while( count < n*10 )
    {

     if(count%10==0){
       fin >> Z[z] ;
       cout<<count<<"and"<<Z[z]<<"and"<<z<<endl;
       z++;}
   
 /*    if(count%10==3){
       fin >> A[a];
       a++;
       cout<<A[a];}
*/
     count++;
    }
    
    fin.close();
//    cout<<Z[10]<<"and";cout<<A[10];


}
