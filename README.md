# Sistema-Estoque-C
# Descrição do Sistema 
O sistema de controle de estoque foi desenvolvido com o objetivo de automatizar e 
facilitar a organização de produtos em empresas. Ele permite a gestão eficiente de 
clientes, fornecedores e produtos, oferecendo funcionalidades como: 
• Cadastro de novos clientes, fornecedores e produtos. 
• Edição de informações previamente cadastradas. 
• Busca por registros específicos. 
• Visualização detalhada dos dados armazenados. 
• Realizar Compra dos produtos para emitir na nota fiscal.

Além disso, sempre que uma compra é realizada, o sistema gera uma nota fiscal e 
atualiza os dados dos produtos (quantidade que é subtraída). Assim garantindo um 
registro formal da transação para o cliente(salva em um arquivo). 

# Estrutura do Código 
# O código foi organizado em seis arquivos de cabeçalho, que separam diferentes funcionalidades do sistema: 
• Cliente.h – Gerencia operações relacionadas aos clientes. 
• Produto.h – Responsável pelo controle dos produtos cadastrados. 
• Fornecedor.h – Lida com informações dos fornecedores. 
• NotaFiscal.h – realiza a compra dos produtos e gerencia as notas fiscais. 
• Menus.h – Contém as interfaces de navegação do usuário. 
• Struct.h – Define as estruturas de dados utilizadas no sistema. 
• Endereco.h – Define a funções do endereço. 

O arquivo main.c é o ponto de entrada do programa, onde todas essas funcionalidades 
são integradas e executadas. Essa estrutura modular melhora a organização do código e 
facilita a manutenção e a escalabilidade do sistema. 

Arquivos 
Clientes.txt – arquivo que armazena dados dos clientes. 
Produtos.txt – arquivo que armazena dados dos produtos. 
Fornecedores.txt – arquivo que armazena dados dos fornecedores. 
NotasFiscais.txt – arquivo que armazena dados da nota fiscal. 
Temp.txt – arquivo temporário utilizado nas funções de editar(Produto, Cliente, 
Fornecedor para atualizar dados). 

# Técnicas Utilizadas 
Para garantir eficiência e organização, utilizamos diversas técnicas de programação, 
incluindo: 
• Manipulação de arquivos, permitindo o armazenamento e recuperação de 
dados. 
• Alocação dinâmica de memória, otimizando o uso de recursos. 
• Structs(estruturas), estruturando melhor os dados. 
• Ponteiros, tornando o código mais eficiente. 
• Funções, facilitando a reutilização e manutenção do código. 
• Etc. 
