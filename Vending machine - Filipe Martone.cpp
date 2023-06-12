#include<iostream>
#include<string>
using namespace std;


float calcula_troco(float a, float b) {  //calcula o troco devido e exibe mensagem de finaliza�ao da operacao para o usu�rio
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

int inventario(string produtos[10], int estoque[10]) { //recebe 2 arrays (nome dos produtos e estoque) e gera um invent�rio
    int i;
    cout << "Inventario: " << endl << endl;
    for (i = 0; i < 10; i++) {
        cout << produtos[i] << " - Quantidade: " << estoque[i] << endl;
    }
    endl;
    return 0;
}

float calcula_faturamento_possivel(int estoque[10], float preco[10]) { //recebe 2 arrays (estoque e pre�o) e calcula o faturamento poss�vel
    int i;
    float soma = 0;
    for (i = 0; i < 10; i++) {                //Percorre o array de estoque e multiplica a quantidade de produtos pelo pre�o armazenado no outro array
        soma += (estoque[i] * preco[i]);
    }
    return soma;
}


int main () {

string lista_produtos[10] = {"[1] Coca-Cola", "[2] Refresco de tamarindo", "[3] Guarana Jesus", "[4] Agua", "[5] Tubaina",\
"[6] Cheetos", "[7] Chocolate", "[8] Lanche natural", "[9] Doritos", "[10] Chiclete"};  //array de strings que lista de todos os produtos e seus c�digos
int estoque[10] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10};    //array com as quantidades iniciais de produtos (m�ximo 10)
float preco[10] = {5.5, 4.0, 3.5, 1.5, 2.5, 5.6, 7.5, 8.0, 12.0, 1.0};     //array com os pre�os de cada produto
float faturamento_atual, faturamento_possivel, pagamento;
int i, opcao, codigo_adm, quantidade_adm;  //vari�veis _adm s� funcionam no modo administrador

faturamento_atual = 0;

while (true) {

    cout << "Qual a boa de hoje, fatequer? Digite o codigo do produto ou 0 para entrar no modo administrador: " << endl << endl;
    for (i = 0; i < 10; i++) {                  //Percorre o array com o nome dos produtos e o array com seus pre�os e exibe para o usu�rio
        cout << lista_produtos[i] << " - R$ " <<  preco[i] << endl;
    }
    cin >> opcao;

    while (opcao == 0) {        //Abre menu administrador. J� exibe o invent�rio, o faturamento atual e poss�vel, e d� a op��o de reposi��o de estoque
            cout << "Bem-vindo(a), administrador(a)!" << endl << endl;
            inventario(lista_produtos, estoque);       //chama a fun��o de invent�rio
            faturamento_possivel = calcula_faturamento_possivel(estoque, preco);     //chama a fun��o que calcula faturamento poss�vel
            cout << "Faturamento atual: R$ " << faturamento_atual << endl << "Faturamento possivel: R$ " << faturamento_possivel << endl << endl;
            cout << "Digite o codigo e a quantidade do produto que deseja repor, ou 0 para retornar ao menu principal" << endl;
            cout << "Codigo do produto: ";
            cin >> codigo_adm;

            if (codigo_adm == 0) {   //Volta ao menu principal
                break;
            }

            while (codigo_adm > 10) {    //Valida o c�digo inserido
                cout << "Codigo invalido. Digite novamente: ";
                cin >> codigo_adm;
            }

            cout << "Quantidade: ";
            cin >> quantidade_adm;

            while ((quantidade_adm + estoque[codigo_adm - 1]) > 10) {  //Calcula quantas unidades ainda podem ser repostas (m�x. 10). Exibe msg caso ultrapasse 10.
                cout << "Voce pode repor no maximo " << 10 - estoque[codigo_adm - 1] << " unidade(s) desse produto. Insira a quantidade novamente: ";
                cin >> quantidade_adm;
            }

            estoque[codigo_adm - 1] += quantidade_adm;  //atualiza o estoque
            cout << "Voce repos " << quantidade_adm << " unidade(s) do produto " << lista_produtos[codigo_adm - 1] << endl << endl;
    }

    if (opcao > 0) {
        while (opcao > 10) {                 //verifica se o c�digo � v�lido
            cout << "Codigo invalido. Digite novamente: ";
            cin >> opcao;
        }

        while (estoque[opcao - 1] == 0) {    //verifica se h� o produto no estoque
            cout << "Voce escolheu: " << lista_produtos[opcao - 1] << endl << "Produto esgotado. Escolha outra opcao ou 0 para cancelar: ";
            cin >> opcao;
            if (opcao == 0) {
                break;
            }
        }

        if (estoque[opcao - 1] > 0) {        //calcula o troco, atualiza o estoque e o faturamento
            cout << "Voce escolheu: " << lista_produtos[opcao - 1] << endl << "Faca o pagamento, por favor: ";
            cin >> pagamento;
            while (pagamento < preco[opcao - 1]) {    //Verifica se o valor inserido � menor do que o pre�o e avisa o usu�rio
                cout << "Valor insuficiente. Coloque um valor maior: ";
                cin >> pagamento;
        }

        calcula_troco(pagamento, preco[opcao - 1]);   //Chama a fun��o que calcula o troco e exibe a mensagem final
        estoque[opcao - 1] -= 1;  //atualiza o estoque
        faturamento_atual += preco[opcao - 1];   //atualiza o faturamento atual
    }
    }
}
return 0;
}
