
#include "Translator.h"

//------------------------------------------------------------------------------
//int main(int argc, char* argv[])
void main()
{

        char cur_char;  //������� ��������� �� ����� ������
        string tr,opd,tm,ex,opr,st,in_file,test_str;
        tr = "translator.txt";
        opd = "operand.txt";
        tm = "term.txt";
        ex = "expression.txt";
        opr = "operator.txt";
        st = "stack.txt";

        in_file = "input.txt";
        //���������� �������� "����������"
        translator_sm trans(tr,opd,tm,ex,opr,st);
        //����� �������� "����������"
        trans.reset();


        //��������� �������� ����� ��������� � ������� ������
       	ifstream input_file (in_file.c_str());
	    if (!input_file) {
		cout << "\nError reading \"input.txt\". No such file!";
		getch();
		//exit(1);
        }

        //����������� ������ ����
       while (!input_file.eof()){

                input_file.get(cur_char);
                cout << cur_char;
                if (cur_char != '\n') trans.input(cur_char);
        }


        cout << "\nEnd.";
        getch();
 //       return 0;
}
