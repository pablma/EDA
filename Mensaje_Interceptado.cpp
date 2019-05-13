#include <iostream>
#include <stack>
#include <string>


void almacena_mensaje(std::stack<char>& stack_par, std::stack<char>& stack_impar, std::string msg);
bool es_vocal(char c);
std::string descifra_mensaje1(std::stack<char>& stack_par, std::stack<char>& stack_impar);
std::string descifra_mensaje2(std::string msg);


//El coste de esta función es O(n), siendo n el tamaño del mensaje
int main()
{
	std::string s;
	std::string input;
	std::getline(std::cin, input);
	

	std::stack<char> stack_par;
	std::stack<char> stack_impar;
	
	while (!input.empty())
	{
		almacena_mensaje(stack_par, stack_impar, input);
		s = descifra_mensaje1(stack_par, stack_impar);
		s = descifra_mensaje2(s);

		std::cout << input << " => " << s << std::endl;
		std::getline(std::cin, input);
	}

	return 0;
}


//El coste de esta función es O(n), siendo n el tamaño del mensaje recibido
void almacena_mensaje(std::stack<char>& stack_par, std::stack<char>& stack_impar, std::string msg)
{
	if (msg.size() % 2 == 0)
	{
		for (int i = 1; i <= msg.size(); i++)
		{
			if (i % 2 == 0)
				stack_par.push(msg[msg.size() - i]);
			else
				stack_impar.push(msg[i]);
		}
	}
	else
	{
		for (int i = 0; i < msg.size(); i++)
		{
			if (i % 2 == 0)
				stack_par.push(msg[(msg.size() - 1) - i]);
			else
				stack_impar.push(msg[i]);
		}
	}

}


//El coste de esta función es O(n), siendo n el tamño de la pila
std::string descifra_mensaje1(std::stack<char>& stack_par, std::stack<char>& stack_impar)
{
	std::string s;

	int tam = stack_par.size();

	for (int i = 0; i < tam; i++)
	{
		s.push_back(stack_par.top());
		stack_par.pop();
	}

	tam = stack_impar.size();

	for (int i = 0; i < tam; i++)
	{
		s.push_back(stack_impar.top());
		stack_impar.pop();
	}

	return s;
}


//El coste de esta función es O(n) siendo n el tamaño de la pila
std::string descifra_mensaje2(std::string msg)
{
	std::stack<char> stack;
	std::string code;


	for (int i = 0; i < msg.size(); i++)
	{
		if (!es_vocal(msg[i]))
		{
			stack.push(msg[i]);
		}
		else if(stack.size() > 0)
		{
			int tam = stack.size();
			for (int j = 0; j < tam; j++)
			{
				code.push_back(stack.top());
				stack.pop();
			}
			code.push_back(msg[i]);
		}
		else
			code.push_back(msg[i]);
	}

	if (stack.size() > 0)
	{
		int tam = stack.size();
		for (int i = 0; i < tam; i++)
		{
			code.push_back(stack.top());
			stack.pop();
		}
	}


	return code;
}


//El coste de esta función es "constante"/"lineal" pues siempre el tamaño de vocales es 11, por lo que estaría en O(11)
bool es_vocal(char c)
{
	std::string vocales = "aAeEiIoOuU";
	bool vocal = false;

	int i = 0;
	
	while (i < vocales.size() && !vocal)
	{
		if (c == vocales[i])
			vocal = true;
		i++;
	}

	return vocal;
}