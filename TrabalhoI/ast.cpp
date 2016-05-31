#include "ast.h"

using namespace AST;

/*Metodos de impressao*/
/*Imprime o valor do nodo quando o mesmo for inteiro*/
void Integer::printTree(){
    std::cout << "(valor inteiro " << value << ")";
    return;
}

/*Imprime o valor do nodo quando o mesmo for real*/
void Doubler::printTree(){
    std::cout << "(valor real " << value << ")";
    return;
}

/*Imprime o valor do nodo quando o mesmo for booleano*/
void Boolean::printTree(){
    std::cout << "(valor booleano " << tipoParaString() << ")";
    return;
}

/*Imprime o arranjo, seu tipo e seu indice quando o nodo for do tipo arranjo*/
void Arranjo::printTree(){
    std::cout << "arranjo"<< 
    AST::tipoParaString(dynamic_cast<Variable*>(var)->tipo)
    << std::endl << "{+indice: ";
    indice->printTree();
    std::cout << "}";
}

/*Imprime o valor das operacoes binarias criadas na gramatica. Cada case influencia em uma operacao diferente*/
void BinOp::printTree(){

    switch(op){
        case Tipos::assign: 
            std::cout << "Atribuicao de valor para ";
            left->printTree(); 
            std::cout << ": "; 
            right->printTree(); 
        break;

        case Tipos::plus: 
            std::cout << "("; 
            left->printTree(); 
            std::cout << " (soma) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;

        case Tipos::sub: 
            std::cout << "("; left->printTree(); 
            std::cout << " (subtracao) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;

        case Tipos::times:
            std::cout << "("; left->printTree(); 
            std::cout << " (multiplicacao) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;

        case Tipos::divi: 
            std::cout << "("; 
            left->printTree(); 
            std::cout << " (divisao) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;
        
        case Tipos::maior: 
            std::cout << "("; left->printTree(); 
            std::cout << " (maior que) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;

        case Tipos::menor: 
            std::cout << "("; left->printTree(); 
            std::cout << " (menor que) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;


        case Tipos::maiorigual: 
            std::cout << "("; left->printTree(); 
            std::cout << " (maior ou igual que) "; 
            right->printTree();
            std::cout << ")"; 
        break;

        case Tipos::menorigual: 
            std::cout << "("; left->printTree(); 
            std::cout << " (menor ou igual que) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;
        
        case Tipos::ande: 
            std::cout << "("; left->printTree(); 
            std::cout << " (AND) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;

        case Tipos::ore: 
            std::cout << "("; left->printTree(); 
            std::cout << " (OR) "; 
            right->printTree(); 
            std::cout << ")"; 
        break;
       
        default: std::cout << "Operador nao tratado" << std::endl; break;
    }  
}

/*Imprime cada linha de insercao respectivamente*/
void Block::printTree(){
    for (Node* line: lines) {
        line->printTree();
        std::cout << std::endl;
    }
}

/*Imprime as informacoes das variaveis criadas no programa, juntamente com seu tipo*/
void Variable::printTree(){
    if (next != NULL){
        next->printTree();
        std::cout << ", " << id;
    } else {
        std::cout << "variavel do tipo" << AST::tipoParaString(tipo) << id;
    }
}

/*Imprime uma operacao unaria. A unica por enquanto no programa eh a operacao de declaracao (tanto de arranjos como variaveis "comuns")*/
void UniOp::printTree(){
    switch(op){
        case Tipos::declaracao:
            std::cout << "Declaracao de ";
            node->printTree();
        break;

        case Tipos::unario: 
            std::cout << "(menor unario" << AST::tipoParaString(node->tipo) << ")";
            node->printTree();  
        break;

        case Tipos::unibool: 
            std::cout << "(menor unario booleano)";
            node->printTree();  
        break;

        case Tipos::coercao:
            std::cout << "(coercao de valor de ";
            node->printTree();
            std::cout << " para real)";
            node->tipo = Tipos::real;
        break;

        default: std::cout << "Operacao nao reconhecida!!!" << std::endl;
    }
}

/*Imprime a condicao, quando a mesma aparecer na arvore.
Deve-se atentar ao fato de que a mesma imprimira o corpo do else somente
se ha algum nodo compondo este corpo*/
void Condicao::printTree(){
    std::cout << "Expressao condicional " << std::endl;
    std::cout << "+se: " << std::endl;
    condicao->printTree();
    std::cout << "\n+entao: " << std::endl;
    corpoIf->printTree();

    if(corpoElse != NULL){
    std::cout << "\n+senao: " << std::endl;
    corpoElse->printTree();
    }

    std::cout << "\nFim expressao condicional" << std::endl;
}

/*Imprime a estrutura do numero complexo, com seu id e componentes*/
void Complexo::printTree(){
    std::cout << "Definicao tipo: " << dynamic_cast<Variable*>(var)->id << std::endl;
    std::cout << "+componentes:" << std::endl;
    for (Node* line: escopoComplexo->lines) {
        line->printTree();
        std::cout << std::endl;
    }
    std::cout << "Fim definicao" << std::endl;
}

/*Funcao que recebe um tipo e retorna uma string, ajudando na impressao das informacoes do nodo que contenha tipo*/
std::string AST::tipoParaString(Tipos::Tipo tipo){
    switch(tipo){
        case Tipos::inteiro : return " inteiro ";
        case Tipos::real : return " real ";
        case Tipos::booleano : return " booleano ";
        default : return " indefinido ";
    }
}

/*Realiza coercao dos nodos necessarios*/
AST::Node* AST::realizaCoercao(std::string id, AST::Node* left, AST::Node* right, ST::SymbolTable* symtab){
    if(Tipos::necessitaCoersao(left->tipo, right->tipo)){
        symtab->realizaCoercao(id);
        std::cout << "Erro semantico: operacao de assign esperava dois tipos compativeis, mas recebeu " << Tipos::tipoParaString(right->tipo) << " e " << Tipos::tipoParaString(left->tipo) << std::endl;
        return new AST::UniOp(left, Tipos::coercao, Tipos::real);
    }
   return left;
}

/*Imprime o laco while declarado pelo usuario. O mesmo imprime tanto a condicao quanto o corpo da estrutura na ordem em que os mesmos aparecem*/
void Laco::printTree(){
    std::cout << "Laco" << std::endl;
    std::cout << "+enquanto: ";
    condicaoLaco->printTree(); std::cout << "\n";
    std::cout << "+faca: " << std::endl;
    corpoLaco->printTree(); std::cout << "\n";
    std::cout << "Fim laco" << std::endl;
}

/*Imprime quando ocorre a declaração de um função.*/
void Funcao::printTree(){
    std::cout << "Declaração da função "<<AST::tipoParaString(tipo)<<": "<<id<<std::endl;
    std::cout<<"+parametros:"<<std::endl;

    if(parametros.size() == 0) {
        std::cout<<"sem parametros"<<std::endl;
    }else if (parametros.at(parametros.size() - 1) != NULL && parametros.size() > 0){
        parametros.at(parametros.size() - 1)->printTree();
        std::cout<<" "<<std::endl;
    } 
    std::cout<<"Fim declaração."<<std::endl;
}

/*Imprime quando ocorre uma definição de uma função.*/
void DefineFuncao::printTree(){
    std::cout << "Definição de função "<<AST::tipoParaString(tipo)<<": "<<id<<std::endl;

    std::cout<<"+parametros:"<<std::endl;
    if(parametros.size() == 0) {
        std::cout<<"sem parametros"<<std::endl;
    } else 
    if(parametros.at(parametros.size() - 1) != NULL && parametros.size() > 0){
        parametros.at(parametros.size() - 1)->printTree();
        // std::cout<<" "<<std::endl;
    }
    std::cout<<" "<<std::endl;
    std::cout<<"+corpo:"<<std::endl;
     if (body != NULL){
        body->printTree();
    }
    std::cout<<"Fim definição."<<std::endl;
}

/*Imprime sempre que houver um retorno em uma função.*/
void Retorno::printTree(){
    std::cout<<"Retorno de função: "<<std::endl;
     if (ret != NULL){
        ret->printTree();
    }
}








