# Sistema de Manutenção de Contas Bancárias

## Sobre o Projeto

Este projeto foi desenvolvido em linguagem C com o objetivo de praticar a manipulação de arquivos binários e o acesso direto a registros utilizando as funções da biblioteca padrão da linguagem.

O sistema permite realizar operações de manutenção de contas bancárias, armazenando os dados dos clientes em um arquivo binário de tamanho fixo.

## Funcionalidades

- Cadastrar um novo cliente em uma posição específica do arquivo.
- Consultar um cliente pelo número da conta.
- Atualizar o saldo de um cliente.
- Encerrar uma conta (remover cliente).
- Listar todos os clientes cadastrados.
- Reiniciar a leitura do arquivo utilizando `rewind()`.
- Encerrar o sistema.

## Estrutura do Registro

Cada cliente é armazenado utilizando a seguinte estrutura:

```c
typedef struct {
    char nome[30];
    unsigned int numero_conta;
    float saldo;
} Cliente;
```

Como todos os registros possuem tamanho fixo, é possível acessar qualquer posição diretamente no arquivo por meio da função `fseek()`.

## Conceitos Aplicados

### Arquivos Binários

Os dados dos clientes são armazenados no arquivo:

```text
usuarios.dat
```

A utilização de arquivos binários permite gravar e recuperar estruturas completas de forma eficiente.

### fwrite()

Utilizada para gravar registros no arquivo.

Exemplo:

```c
fwrite(&cliente, sizeof(Cliente), 1, arqptr);
```

### fread()

Utilizada para ler registros armazenados no arquivo.

Exemplo:

```c
fread(&cliente, sizeof(Cliente), 1, arqptr);
```

### fseek()

Permite posicionar o ponteiro do arquivo em uma posição específica para acesso direto aos registros.

Exemplo:

```c
fseek(arqptr, posicao * sizeof(Cliente), SEEK_SET);
```

### rewind()

Reposiciona o ponteiro do arquivo no início, permitindo repetir leituras.

Exemplo:

```c
rewind(arqptr);
```

## Como Executar

### Compilação

Utilizando GCC:

```bash
gcc main.c -o sistema
```

### Execução

Linux/Mac:

```bash
./sistema
```

Windows:

```bash
sistema.exe
```

## Menu do Sistema

```text
1 - Cadastrar cliente
2 - Consultar cliente
3 - Atualizar saldo
4 - Encerrar conta
5 - Listar clientes
6 - Restaurar leitura (rewind)
7 - Encerrar sistema
```

## Atendimento aos Requisitos da Atividade

| Requisito | Implementação |
|------------|--------------|
| Cadastro de cliente em posição específica | Utilização de `fseek()` para posicionamento do registro |
| Consulta por número da conta | Busca utilizando `fread()` |
| Atualização de saldo | Leitura e regravação do registro |
| Encerramento de conta | Sobrescrita do registro com dados vazios |
| Listagem de clientes | Leitura sequencial utilizando `fread()` |
| Reinício da leitura | Utilização da função `rewind()` |
| Arquivo binário | Armazenamento em `usuarios.dat` |
| Registros de tamanho fixo | Estrutura `Cliente` |

## Observações

- Os registros possuem tamanho fixo.
- O encerramento de conta é realizado sobrescrevendo o registro com valores vazios.
- Para repetir a listagem dos clientes após uma leitura completa do arquivo, é necessário utilizar a opção que executa `rewind()`.
- O projeto foi desenvolvido para fins acadêmicos e demonstra o uso de manipulação de arquivos binários em C.

## Autor

Desenvolvido como atividade prática da disciplina de Programação em C.
