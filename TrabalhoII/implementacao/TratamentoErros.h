#pragma once

#include <iostream>
#include <vector>

namespace Tipos {
	enum Tipo { inteiro, real, booleano, indefinido, complexo, string};
	enum Operation { plus, sub, times, divi, assign, maior, menor, maiorigual, menorigual, ande, ore, unibool, chamadaFuncao, unario, declaracao, igual, diferente, coercao, defineIndiceArranjo, defineCondicaoLaco, usoClasse };

	Tipo opUnaria( Tipo tipoRecebido, Operation op );
	Tipo opBinaria( Tipo tipoNodoEsquerda, Tipo tipoNodoDireita, Operation op );

	void erroCondicao( Operation operacao, Tipo primeiroRecebido, Tipo segundoRecebido, Tipo primeiroEsperado, Tipo segundoEsperado );
	void erroTipagem( Operation operacao, Tipo primeiroRecebido, Tipo segundoRecebido, Tipo esperado );
	void tiposIncompativeis( Tipo primeiroTipo, Tipo segundoTipo, Operation operacao );
	bool precisaCoersao( Tipo tipoNodoEsquerda, Tipo tipoNodoDireita );
	void erroIndiceArranjo( Tipo primeiroTipo, Tipo segundoTipo );
	void erroCondicaoLaco( Tipo esperado, Tipo recebido );

	std::string tipoParaString( Tipo tipo, bool ehMasc );
	std::string opParaString( Operation tipo );
	bool necessitaCoersao( Tipo tipoNodoEsquerda, Tipo tipoNodoDireita );

}
