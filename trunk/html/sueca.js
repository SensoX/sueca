const NAIPES = new Array("Espadas", "Copas", "Paus", "Ouros");
const NOMES_NAIPES = new Array("E", "C", "P", "O");
const FIGURAS = new Array("Ás", "Bisca", "Rei", "Valete", "Dama", "Sena", "Quina", "Quadra", "Terno", "Duque");
const NOMES_FIGURAS = new Array("A", 7, "K", "J", "Q", 6, 5, 4, 3, 2);
const PONTOS = new Array(11, 10, 4, 3, 2, 0, 0, 0, 0, 0);
const VALOR = new Array(9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
const JOGADORES = new Array("Humano", "Virtual");

function Carta(naipe, figura) {
	this.naipe = naipe;
	this.figura = figura;
	
	this.pontos = function () {
		return PONTOS[this.figura];
	}
	
	this.valor = function () {
		return VALOR[this.figura];
	}
	
	this.toString = function () {
		return FIGURAS[this.figura] + ' de ' + NAIPES[this.naipe];
	}
	
	this.toStringCores = function () {
		if (this.naipe == 0 || this.naipe == 2)
			return '<font color="black">' + FIGURAS[this.figura] + ' de ' + NAIPES[this.naipe] + "</font>";
		if (this.naipe == 1 || this.naipe == 3)
			return '<font color="red">' + FIGURAS[this.figura] + ' de ' + NAIPES[this.naipe] + "</font>";
	}
	
	this.toStringNome = function () {
		return NOMES_NAIPES[this.naipe] + NOMES_FIGURAS[this.figura];
	}
}

function Baralho() {
	var i, j;
	
	this.cartas = new Array();
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 10; j++)
			this.cartas.push(new Carta(i, j));
	
	this.toString = function () {
		return this.cartas.toString();
	}
}

function Mao() {
	this.cartas = new Array();
	
	this.sort = function () {
		this.cartas.sort(function (c1, c2) {
			return (c1.naipe * 10 + c1.figura) - (c2.naipe * 10 + c2.figura)
		});
	}
	
	this.splice = function (carta) {
		return this.cartas.splice(carta, 1)[0];
	}
	
	this.toString = function () {
		var i,
		cartas = this.cartas,
		r = "";
		
		if (cartas[0])
			r += '' + 0 + " - " + cartas[0] + ' ';
		for (i = 1; cartas[i]; i++)
			r += '| ' + i + " - " + cartas[i] + ' ';
		
		return r;
	}
	
	this.toStringCores = function () {
		var i,
		cartas = this.cartas,
		r = "";
				
		if (cartas[0]) {
			if (cartas[0].naipe == 0 || cartas[0].naipe == 2)
				r += '<font color="black">' + 0 + " - " + cartas[0].toString() + "</font>";
			if (cartas[0].naipe == 1 || cartas[0].naipe == 3)
				r += '<font color="red">' + 0 + " - " + cartas[0].toString() + "</font>";
		}
		
		for (i = 1; cartas[i]; i++) {
			if (cartas[i].naipe == 0 || cartas[i].naipe == 2)
				r += '<font color="black">' + ' | ' + i + " - " + cartas[i].toString() + ' ' + "</font>";
			if (cartas[i].naipe == 1 || cartas[i].naipe == 3)
				r += '<font color="red">' + ' | ' + i + " - " + cartas[i].toString() + ' ' + "</font>";
		}
		
		return r;
	}
}

function Jogador(tipo, nome) {
	this.tipo = tipo;
	this.nome = nome;
	this.mao = new Mao();
	
	this.toString = function () {
		var r = "";
		
		r += this.nome + " - " +  JOGADORES[this.tipo] + "\n";
		r += this.mao.toString();
		
		return r;
	}
}

function Equipa(nome, ja, jb) {
	this.nome = nome;
	this.jogadores = new Array(ja, jb);
	this.pontos = 0;
	
	ja.equipa = this;
	jb.equipa = this;
	
	this.toString = function () {
		var jogadores = this.jogadores,
		r = "";
		
		r += this.nome;
		r += jogadores[0].toString() + "\n";
		r += jogadores[1].toString();
		
		return r;
	}
}

function Mesa() {
	this.criar_jogadores = function () {
		var j0, j1, j2, j3;
		
		j0 = new Jogador(0, "Jogador 0");
		j1 = new Jogador(1, "Jogador 1");
		j2 = new Jogador(1, "Jogador 2");
		j3 = new Jogador(1, "Jogador 3");
		this.jogadores = new Array(j0, j1, j2, j3);
	}

	this.criar_equipas = function () {
		var e0, e1,
		jogadores = this.jogadores;
		
		e0 = new Equipa("Equipa 0", jogadores[0], jogadores[2]);
		e1 = new Equipa("Equipa 1", jogadores[1], jogadores[3]);
		this.equipas = new Array(e0, e1);
	}
	
	this.criar_baralho = function () {
		var baralho;
		
		baralho = new Baralho();
		baralho.cartas.shuffle();
		
		this.baralho = baralho;
	}
	
	this.dar_cartas = function () {
		var j, c, jogador,
		jogadores = this.jogadores;
		
		/* 1º Jogador a receber as cartas */
		jogador = Math.floor(Math.random() * 4);
		
		for (j = 0; j < 4; j++) {
			/* Dar Cartas */
			for (c = 0; c < 10; c++)
				jogadores[j].mao.cartas.push(this.baralho.cartas.pop());
				
			/* Definir Trunfo */
			if (j == jogador) {
				this.trunfo = jogadores[j].mao.cartas[0];
			}
			
			/* Ordenar cartas da mão */
			jogadores[j].mao.sort();
		}
	
		/* 1º Jogador a jogar */
		jogador++;
		if (jogador == 4)
			jogador = 0;
	
		/* Iniciar variáveis */
		this.jogador = jogador;
		this.primeiro_jogador = jogador;
		this.humano = false;
		this.baza = 0;
		this.cartas_jogadas = new Array(4);
		
		/* Evento */
		if ($.isFunction(this.cb_cartas_dadas))
			this.cb_cartas_dadas();
	}
	
	/*
	 * return	0 -> Erro
	 *			1 -> Fim do Jogo
	 *			2 -> Jogador Humano
	 *			3 -> Carta Inválida
	 */
	this.jogar = function jogar(pos_carta) {
		var i, vencedor_baza, vencedora,
		equipas = this.equipas,
		jogadores = this.jogadores,
		cartas_jogadas = this.cartas_jogadas;
		
		do {
		//alert(this.jogador);
			if (!this.jogador) {
				if (!this.humano) {
					/* Jogador Humano joga */
					this.humano = true;
					
					return 2;
				} else {
					if (this.is_carta_valida(jogadores[this.jogador].mao.cartas[pos_carta])) {
						cartas_jogadas[this.jogador] = jogadores[this.jogador].mao.cartas.splice(pos_carta, 1)[0];
						this.humano = false;
					} else {
						/* Evento */
						if ($.isFunction(this.cb_carta_invalida))
							this.cb_carta_invalida();
							
						return 3;
					}
				}
			} else {
				/* Jogador Virtual joga */
				this.jogar_virtual(0);
			}
			
			/* Evento */
			if ($.isFunction(this.cb_jogador_jogou))
				this.cb_jogador_jogou();
				
			/* Incrementar Jogador */
			this.jogador++;
			if (this.jogador == 4)
				this.jogador = 0;
			
			/* Fim da baza */
			if (this.jogador == this.primeiro_jogador) {
				/* Calcular jogador vencedor da baza*/
				this.vencedor_baza = vencedor_baza = this.calcular_vencedor_baza();
				
				if (jogadores[vencedor_baza].equipa == this.equipas[0])
					this.vencedora_baza = 0;
				else if (jogadores[vencedor_baza].equipa == this.equipas[1])
					this.vencedora_baza = 1;
				
				/* Somar pontos */
				for (i = 0; i < 4; i++)
					jogadores[vencedor_baza].equipa.pontos += cartas_jogadas[i].pontos();
				
				/* Evento */
				if ($.isFunction(this.cb_baza_terminou))
					this.cb_baza_terminou();
				
				/* Iniciar variáveis para a próxima baza*/
				this.primeiro_jogador = vencedor_baza;
				this.jogador = vencedor_baza;
				this.cartas_jogadas = cartas_jogadas = new Array(4);
				this.baza++;
			}
		} while (this.baza < 10);
		/*if (this.baza < 10) {
				setTimeout(function () {alert(1); alert(this.mesa.jogar()); alert(2);}, 2000);
				return;
		}*/
		
		/* Calcular equipa vencedora do jogo */
		
		if (equipas[0].pontos > equipas[1].pontos)
			vencedora = 0;
		else if (equipas[0].pontos < equipas[1].pontos)
				vencedora = 1;
			else
				/* Empate */
				vencedora = -1
				
		this.vencedora = vencedora;
		
		/* Evento */
		if ($.isFunction(this.cb_jogo_terminou))
			this.cb_jogo_terminou();
			
		return 1;
	}
	
	/*
	 * tipo		0 -> Joga uma carta qualquer aleatóriamente
	 *			1 -> 
	 *			2 -> 
	 */
	this.jogar_virtual = function (tipo) {
		var i,
		pos_carta = -1,
		jogador = this.jogador,
		jogadores = this.jogadores,
		cartas_jogadas = this.cartas_jogadas,
		cartas = jogadores[jogador].mao.cartas;
		
		switch (tipo) {
			case 0:
				cartas.shuffle();
				
				for (i = 0; cartas[i] && pos_carta == -1; i++)
					if (this.is_carta_valida(cartas[i]))
						pos_carta = i;
						
				cartas_jogadas[jogador] = cartas.splice(pos_carta, 1)[0];
				
				jogadores[jogador].mao.sort();
				break;
			case 1:
				
				break
		}
	}
		
	this.is_carta_valida = function (carta) {
		var i,
		pos_carta = -1,
		jogador = this.jogador,
		jogadores = this.jogadores,
		primeiro_jogador = this.primeiro_jogador,
		cartas_jogadas = this.cartas_jogadas,
		cartas = jogadores[jogador].mao.cartas;
		
		/* Verificar primeiro se a carta é do jogador que está a jogar */
		for (i = 0; cartas[i] && pos_carta == -1; i++)
			if (cartas[i] == carta)
				pos_carta = i;
		
		if (pos_carta != -1) {
			/* Verdadeiro se for o primeiro a jogar. Pode jogar qualquer carta. */
			if (jogador == primeiro_jogador)
				return true;
		
			/* Verdadeiro se a carta for do mesmo naipe que a primeira carta jogada. */
			if (cartas[pos_carta].naipe == cartas_jogadas[primeiro_jogador].naipe)
				return true;
		
			/* Falso se tiver uma carta com o mesmo naipe que a primeira carta jogada. */
			for (i = 0; cartas[i]; i++)
				if (cartas[i].naipe == cartas_jogadas[primeiro_jogador].naipe)
					return false;
			
			/* Verdadeiro senão nenhuma das anteriores. */
			return true;
		}
		
		return false;
	}
	
	this.calcular_vencedor_baza = function () {
		var i, vencedor,
		primeiro_jogador = this.primeiro_jogador,
		cartas_jogadas = this.cartas_jogadas,
		naipe_trunfo = this.trunfo.naipe,
		existe_trunfo = false;
		
		/* Vencedor se for o primeiro jogador (caso base). */
		vencedor = primeiro_jogador;
		
		/* Vencedor se tiver maior trunfo. */
		for (i = 0; i < 4 && !existe_trunfo; i++) {
			if (cartas_jogadas[i].naipe == naipe_trunfo)
			{
				vencedor = i;
				existe_trunfo = true;
			}
		}
		
		if (existe_trunfo) {
			for (i = 0; i < 4; i++)
				if (cartas_jogadas[i].naipe == naipe_trunfo)
					if (cartas_jogadas[i].valor() > cartas_jogadas[vencedor].valor())
						vencedor = i;
							
			return vencedor;
		}
		
		/* Vencedor se tiver carta do mesmo naipe que o primeiro jogador com mais pontos. */
		for (i = 0; i < 4; i++)
			if (cartas_jogadas[i].naipe == cartas_jogadas[primeiro_jogador].naipe)
				if (cartas_jogadas[i].valor() > cartas_jogadas[vencedor].valor())
						vencedor = i;
						
		return vencedor;
	}
	
	this.toString = function () {
		var equipas = this.equipas;
		
		return equipas[0].toString() + "\n" + equipas[1].toString();
	}
}
