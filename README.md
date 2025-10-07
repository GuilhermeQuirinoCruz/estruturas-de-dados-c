# Estruturas de Dados em linguagem C

## Sobre
Projeto desenvolvido com o intuito de aprofundar os conhecimentos na implementação e no funcionamento das estruturas de dados selecionadas, que são capazes de aceitar qualquer tipo de dado a partir de uma implementação básica.

## Estruturas Planejadas
- [x] Array
- [ ] Lista ligada
- [ ] Fila
- [ ] Pilha
- [ ] Deque
- [ ] Hashtable
- [ ] Árvore binária
- [ ] Árvore AVL

## Instruções
### Dependências
- Um compilador de C à sua escolha 
  - Recomendado: [GCC](https://gcc.gnu.org/)

### Como utilizar
- Clone o repositório do projeto
```bash
$ git clone https://github.com/GuilhermeQuirinoCruz/estruturas-de-dados-c
```

- **(Atenção)** Caso esteja utilizando Windows, talvez seja necessário configurar a saída do console para que os caracteres sejam exibidos corretamente
```bash
$ # Importe a biblioteca
$ include <windows.h>

$ # Inclua uma vez antes de imprimir algo no console, preferencialmente no método main
$ SetConsoleOutputCP(65001);
```

- Compile um arquivo, incluindo os arquivos importados
```bash
$ gcc -o arquivo_de_saida.out arquivo.c ../pasta/arquivo_2.c ../types/integer.c
```

- Execute o arquivo compilado
```bash
$ ./arquivo_de_saida.out
```

## Linha do tempo e próximos passos
- [x] Organização do projeto
- [x] Implementação de uma estrutura base - Array
- [x] Implementação de um tipo de dado básico - Integer
- [ ] Implementação das demais estruturas
- [ ] Implementação de tipos de dados mais complexos
- [ ] Criação de um makefile para facilitar o processo de compilação e execução