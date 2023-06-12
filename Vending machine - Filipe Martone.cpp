#include<iostream>
#include<string>
using namespace std;


float calcula_troco(float a, float b) {  //calcula o troco devido e exibe mensagem de finalizaçao da operacao para o usuário
    float troco;
    troco = a - b;
    if (troco > 0) {
        cout << "Seu troco eh: " << troco << " R$." << endl << "Retire o produto. Obrigado!" << endl << endl;
    }
    else {
        cout << "Retire o produto. Obrigado!" << endl << endl;
    }
    return troco;
}

int inventario(string produtos[10], int estoque[10]) { //recebe 2 arrays (nome dos produtos e estoque) e gera um inventário
    int i;
    cout << "Inventario: " << endl << endl;
    for (i = 0; i < 10; i++) {
        cout << produtos[i] << " - Quantidade: " << estoque[i] << endl;
    }
    cout << endl;
    return 0;
}

float calcula_faturamento_possivel(int estoque[10], float preco[10]) { //recebe 2 arrays (estoque e preço) e calcula o faturamento possível
    int i;
    float soma = 0;
    for (i = 0; i < 10; i++) {                //Percorre o array de estoque e multiplica a quantidade de produtos pelo preço armazenado no outro array
        soma += (estoque[i] * preco[i]);
    }
    return soma;
}


int main () {

string lista_produtos[10] = {"[1] Coca-Cola", "[2] Refresco de tamarindo", "[3] Guarana Jesus", "[4] Agua", "[5] Tubaina",\
"[6] Cheetos", "[7] Chocolate", "[8] Lanche natural", "[9] Doritos", "[10] Chiclete"};  //array de strings que lista de todos os produtos e seus códigos
int estoque[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};    //array com as quantidades iniciais de produtos (máximo 10)
float preco[10] = {5.5, 4.0, 3.5, 1.5, 2.5, 5.6, 7.5, 8.0, 12.0, 1.0};     //array com os preços de cada produto
float faturamento_atual, faturamento_possivel, pagamento;
int i, codigo, codigo_adm, quantidade_adm;  //variáveis _adm só funcionam no modo administrador

faturamento_atual = 0;

while (true) {

    cout << "Qual a boa de hoje, fatequer? Digite o codigo do produto ou 0 para entrar no modo administrador: " << endl << endl;
    for (i = 0; i < 10; i++) {                  //Percorre o array com o nome dos produtos e o array com seus preços e exibe para o usuário
        cout << lista_produtos[i] << " - R$ " <<  preco[i] << endl;
    }
    cin >> codigo;

    while (codigo == 0) {        //Abre menu administrador. Já exibe o inventário, o faturamento atual e possível, e dá a opção de reposição de estoque
            cout << "Bem-vindo(a), administrador(a)!" << endl << endl;
            inventario(lista_produtos, estoque);       //chama a função de inventário
            faturamento_possivel = calcula_faturamento_possivel(estoque, preco);     //chama a função que calcula faturamento possível
            cout << "Faturamento atual: R$ " << faturamento_atual << endl << "Faturamento possivel: R$ " << faturamento_possivel << endl << endl;
            cout << "Digite o codigo e a quantidade do produto que deseja repor, ou 0 para retornar ao menu principal" << endl;
            cout << "Codigo do produto: ";
            cin >> codigo_adm;

            if (codigo_adm == 0) {   //Volta ao menu principal
                break;
            }

            while (codigo_adm > 10) {    //Valida o código inserido
                cout << "Codigo invalido. Digite novamente: ";
                cin >> codigo_adm;
            }

            cout << "Quantidade: ";
            cin >> quantidade_adm;

            while ((quantidade_adm + estoque[codigo_adm - 1]) > 10) {  //Calcula quantas unidades ainda podem ser repostas (máx. 10). Exibe msg caso ultrapasse 10.
                cout << "Voce pode repor no maximo " << 10 - estoque[codigo_adm - 1] << " unidade(s) desse produto. Insira a quantidade novamente: ";
                cin >> quantidade_adm;
            }

            estoque[codigo_adm - 1] += quantidade_adm;  //atualiza o estoque
            cout << "Voce repos " << quantidade_adm << " unidade(s) do produto " << lista_produtos[codigo_adm - 1] << endl << endl;
    }

    if (codigo > 0) {
        while (codigo > 10) {                 //verifica se o código é válido
            cout << "Codigo invalido. Digite novamente: ";
            cin >> codigo;
        }

        while (estoque[codigo - 1] == 0) {    //verifica se há o produto no estoque
            cout << "Voce escolheu: " << lista_produtos[codigo - 1] << endl << "Produto esgotado. Escolha outra opcao ou 0 para cancelar: ";
            cin >> codigo;
            if (codigo == 0) {
                break;
            }
        }

        if (estoque[codigo - 1] > 0) {        //calcula o troco, atualiza o estoque e o faturamento
            cout << "Voce escolheu: " << lista_produtos[codigo - 1] << endl << "Faca o pagamento, por favor: ";
            cin >> pagamento;
            while (pagamento < preco[codigo - 1]) {    //Verifica se o valor inserido é menor do que o preço e avisa o usuário
                cout << "Valor insuficiente. Coloque um valor maior: ";
                cin >> pagamento;
        }

        calcula_troco(pagamento, preco[codigo - 1]);   //Chama a função que calcula o troco e exibe a mensagem final
        estoque[codigo - 1] -= 1;  //atualiza o estoque
        faturamento_atual += preco[codigo - 1];   //atualiza o faturamento atual
    }
    }
}
return 0;
}
