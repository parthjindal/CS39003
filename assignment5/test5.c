int main()  
{  
    int a, b, g;
    int flag=2;
    if(flag==0)
    {
    	a=100;
    	b=25;
    }
    else
    {
    	a=20;
    	if(flag==1)   // nested if else
    		b=5;
    	else
    		b=4;
    }
    return 0;
}  