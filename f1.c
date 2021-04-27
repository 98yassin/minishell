/*
							\"'
							'
							'
							'
							'
							'
							'
							'
							'
							'
							'
							'
							'
*/
int			double_quotes(char *value, int j, char c)
{
	int backslash;

	backslash = 0;
	while (value[j] != '\0' && value[j] != c)
    {
        if (value[j] == '\\')
        {
            backslash = check_backslash(value, j);
            if (backslash % 2 != 0)
            {
                j = j + backslash;
                backslash = 0;
            }else
            {
                j = j + backslash - 1;
                backslash = 0;
            }
        }
        j++;
    }
	return (j);
}



