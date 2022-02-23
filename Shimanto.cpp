#include<bits/stdc++.h>
using namespace std;
int two_r(int r)
{
    return (int)pow(2.0,(double)r);
}
int main()
{
    string str;
    cout<<"Enter data string with 0 and 1 ";
    getline(cin,str);
    char parity_type;
    cout<< "If the parity is even then enter \'e\' and if this is odd  enter \'o\' ";
    cin>>parity_type;
    reverse(str.begin(),str.end());
    int m = str.length();
    bool data[m+1];

    for(int n=1;n<=m;n++)
    {
        if(str[n-1] == '1'){
            data[n] = 1;
        }
        else{
            data[n] = 0;
        }
    }

    int r = 1;
    while(!((m+r+1)<=two_r(r)))
    {
        r++;
    }


    bool send_data[m+r+1];

    int a = 0;
    int b = 1;
    for(int n=1;n<=(m+r);n++)
    {
        if(n == two_r(a))
        {
            send_data[n] = 0;
            a=a+1;
        }
        else
        {
            send_data[n] = data[b];
            b=b+1;
        }
    }

    for(int n=0;n<r;n++)
    {
        for(int k=1;k<=(m+r);k++)
        {
            if(((k>>n)&1) == 1)
            {
                if(k!=two_r(n))
                {
                    send_data[two_r(n)]^=send_data[k];

                }
            }
        }
        if(parity_type == 'o')
        {
            send_data[two_r(n)] = !(send_data[two_r(n)]);
        }
    }

    cout<<"Send Data is : ";
    for(int n=(m+r);n>0;n--)
    {

        cout<<send_data[n];
    }
    cout<<"\n";


    cout<<" Receiving the Data String with 0 and 1 ";
    cin.ignore();
    getline(cin,str);
    reverse(str.begin(),str.end());

    bool receive_data[m+r+1];
    for(int n=1;n<=(m+r);n++)
    {
        if(str[n-1] == '1'){
            receive_data[n] = 1;
        }
        else{
            receive_data[n] = 0;
        }
    }

    int error_pos = 0;
    bool error_correction = false,temp_error = false;
    while(!error_correction)
    {
        bool temp = true;
        for(int n=0;n<r;n++)
        {
            bool parity_Val = 0;
            for(int k=1;k<=(m+r);k++)
            {
                if(((k>>n)&1) == 1)
                {
                    if(k!=two_r(n))
                    {
                    parity_Val^=receive_data[k];

                    }
                }
            }
            if(parity_type == 'o')
            {
                parity_Val=!parity_Val;
            }
            if(parity_Val != receive_data[two_r(n)]){
                error_pos+= two_r(n);
                temp = false;
            }

        }
        if(temp_error == true && temp == false)
        {
        cout<<"Double Bit Error";
            return 0;
        }
        if(temp == false)
        {
            receive_data[error_pos] = !receive_data[error_pos];
            temp_error = true;
        }
        else
        {
            error_correction = true;
        }
    }
    cout<<"Error Detected in Position: "<<error_pos<<endl;


    cout<<"After Correcting CODEWORD is : ";
    for(int n=(m+r);n>0;n--)
    {

        cout<<receive_data[n];
    }
    cout<<"\n";

}

