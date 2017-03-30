
#include "Svetofor.h"

//------------------------------------------------------------------------------
void main()
{
        char cur_char;  //Текущий считанный из файла символ
        string in_file;
        in_file = "input.txt";

        //объявление класса svetofor_sm
        svetofor_sm svetofor("svetofor.txt");
        //Сброс 
        svetofor.reset();


        //открываем файловый поток связанный с входным файлом
       	ifstream input_file (in_file.c_str());
	    if (!input_file) {
		cout << "\nError reading \"input.txt\". No such file!";
		getch();
		//exit(1);
        }

        int  K=0;
        int  D=0;
        int  Z=0;
        int  Kcount=0;
        int  Dcount=0;
        int  Zcount=0;
        string blank("        ");
        string print("        ");

        //Посимвольно читаем файл
       while (!input_file.eof()){

                 input_file.get(cur_char);


//-----------------------------------------------------------------------------
                 if (cur_char=='4'||cur_char=='6')K=1;
                 if (K==1&&Kcount<6){
                     if (cur_char=='2'||cur_char=='3'){
                        print[4]='K';
                      }
                     if (cur_char=='0'){
                        print[4]='K';
                      }
                     Kcount++;
                  }
                 if (Kcount==6 ){
                    K=0;
                    Kcount=0;
                 }
//-----------------------------------------------------------------------------
                 if (cur_char=='2'||cur_char=='6')D=1;
                 if (D==1&&Dcount<4){
                     if (cur_char=='1'||cur_char=='3'){
                        print[5]='D';
                      }
                     if (cur_char=='0'){
                        print[5]='D';
                      }
                     Dcount++;
                  }
                 if (Dcount==4 ){
                    D=0;
                    Dcount=0;
                 }
//----------------------------------------------------------------------------
                svetofor.input(K*4+D*2+Z);
                string y=svetofor.get_result();
                  if (y=="YL r"||y=="R  yl" )Z=1;
                  if (Z==1&&Zcount<2){
                     Zcount++;
                  }
                  if (Zcount==2 ){
                    Z=0;
                    Zcount=0;
                  }
//-----------------------------------------------------------------------------
                 if (cur_char!='\n'){
                   print[0]=cur_char;
                   print+=y;
                   cout<<print;
                   print=blank;
                 }  cout<<'\n';
         }

        cout << "\nEnd.";
        getch();

}
