#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	stack<int> pila;
	int numCasos, numOperandos, resultado;
	numCasos = numOperandos = resultado = 0;
	
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		cin >> numOperandos;
	
		if (numOperandos > 1)
		{
			int j;
			string s;

			getline(cin, s);

			for (j = 1; j < s.size(); j++)
			{		
				
				if(s[j] == '-')				
					pila.top() = - pila.top();				
				else if(s[j] != '+')
					pila.push(s[j] - 48);			
				
			}

			int stack_size = pila.size();

			for (int k = 0; k < stack_size; k++)
			{
				resultado += pila.top();
				pila.pop();
			}	
		}
		else if (numOperandos == 0)
			resultado = 0;
		else
			cin >> resultado;
		
		
		cout << resultado << endl;
		resultado = 0;

	}

	system("pause");

	return 0;
}