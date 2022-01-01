int a;
int b;
int c = 0;
int d = 10;

int main()
{
	int a[5]; // 1D integer array
	int b[5][5]; // 2D integer array
	int i;
	int j;
	int k;

	i = 10;
	j = 20;
	k = 30;

	while(i < j)
	{
		a[i] = i;
		i++;
		j++;
	}

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			for(k = 0; k < 5; k++)
			{
				b[i][j] = i + j + k;
			}
			
		}
	}
	return 1;
}
