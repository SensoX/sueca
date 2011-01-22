const TAMANHO_MARGEM_B = 0.02;
const TAMANHO_MARGEM_C = 0.02;
const TAMANHO_MARGEM_D = 0.02;
const TAMANHO_MARGEM_E = 0.145;
const TAMANHO_MARGEM_F = 0.06;
const TAMANHO_MARGEM_G = 0.20;
const TAMANHO_LETRA = 0.04;
const TAMANHO_RELATIVO_CARTA = 0.14;
/* DIF_ALTURA_LARGURA_CARTA deve sempre ser igual à diferença de largura/altura da carta em .svg */
const DIF_ALTURA_LARGURA_CARTA = 0.8;
const ESPACO_ENTRE_CARTAS = 0.35;
const TIMEOUT = 1000;

$(window).resize(aoRedimensionar);

$(document).ready(function () {
	/* Criar motor do Jogo da Sueca */
	var mesa = new Mesa();
	
	aoRedimensionar();
	
	/* Eventos */
	$("#db").delegate("div.c", "click", function(){
		mesa.jogar($(this).parent().attr("class").substring(1));
	});
	
	$("#db").delegate("div.c", "mouseover", function(){
		$(this).parent()
		.css("z-index", 10);
	});
	
	$("#db").delegate("div.c", "mouseout", function(){
		$(this).parent()
		.css("z-index", $(this).parent().attr("class").substring(1));
	});
	
	/* Preparar CallBacks do Jogo da Sueca */
	mesa.cb_cartas_dadas = function () {
		var i,
		cartas = this.jogadores[0].mao.cartas;
		
		$("#ct > object.c").attr("data", "cartas/" + this.trunfo.toStringNome() + ".svg");
		
		for (i = 0; cartas[i]; i++)
			$("#j0 > .c" + i + " > object.c").attr("data", "cartas/" + cartas[i].toStringNome() + ".svg");
	}
	
	mesa.cb_carta_invalida = function () {
	}
	
	mesa.cb_jogador_jogou = function () {
		var i, cartas,
		jogador = this.jogador,
		baza = this.baza,
		tam_zona = $("#dc").width(),
		largura_carta = $("#j1 > .c0 > object.c").width(),
		espaco_entre_cartas = largura_carta * ESPACO_ENTRE_CARTAS,
		tam_mao = largura_carta + espaco_entre_cartas * (8 - baza);
		
		/* Remover a Carta da Mão do Jogador */
		$("#j" + jogador + " > .c" + (9 - baza)).remove();
		
		/* Efeito da Carta ao jogar */
		//$("#j" + jogador + " > .c0").effect("transfer", {to: "#j0j", className: "ui-effects-transfer"}, "slow");
		
		/* Reposicionar Cartas do Jogador */
		switch (jogador) {
			case 0:				
				cartas = this.jogadores[0].mao.cartas;
				
				$("#j0").css("left", tam_zona / 2 - tam_mao / 2);
				$(".c" + (8 - baza) + " > div.c").css("right", 0);
				
				for (i = 0; cartas[i]; i++)
					$("#j0 > .c" + i + " > object.c").attr("data", "cartas/" + cartas[i].toStringNome() + ".svg");
				break;
			case 1:
				$("#j1").css("bottom", tam_zona / 2 - tam_mao / 2);
				break;
			case 2:
				$("#j2").css("right", tam_zona / 2 - tam_mao / 2);
				break;
			case 3:
				$("#j3").css("top", tam_zona / 2 - tam_mao / 2);
				break;
		}
		
		$("#j" + jogador + "j > object.c").attr("data", "cartas/" + this.cartas_jogadas[jogador].toStringNome() + ".svg");
	}
	
	mesa.cb_baza_terminou = function () {		
		var i,
		vencedora_baza = this.vencedora_baza;
		
		for (i = 0; i < 4; i++)
			$("#j" + i + "j > object.c").removeAttr("data");
		
		if ($("#e" + vencedora_baza + " > object.c").attr("data") == "")
			$("#e" + vencedora_baza + " > object.c").attr("data", "cartas/C.svg");			
	}
	
	mesa.cb_jogo_terminou = function () {
		var
		vencedora = this.vencedora,
		equipas = this.equipas;
		
		$("#ct > object.c").removeAttr("data");
					
		if (this.vencedora != -1) {
			alert("Vencedor: " + equipas[vencedora].nome + ".\n" + equipas[vencedora].pontos + " pontos!");
		} else {
			alert("Empate!\n" + equipas[0].nome + ".\n" + equipas[0].pontos + " pontos.\n" + equipas[1].nome + ".\n" + equipas[1].pontos + " pontos.");
		}
	}
	
	/* Jogar o Jogo da Sueca */
	mesa.criar_jogadores();
	mesa.criar_equipas();
	mesa.criar_baralho();
	mesa.dar_cartas();
	mesa.jogar();
});

function aoRedimensionar() {
	var i, j, tam_mesa, tam_margem, altura_carta, largura_carta, dif_alt_larg_carta, espaco_entre_cartas, tam_mao, tam_zona, tam_letra;
	
	/* Bug no tamanho do viewport do Firefox */
	$("object.c").height(0);
	
	/* Calcular tamanho para a Mesa */
	if ($(window).height() <= $(window).width())
		tam_mesa = $(window).height();
	else
		tam_mesa = $(window).width();
			
	/* Definir tamanho e posição da Mesa */
	$("#da")
	.height(tam_mesa)
	.width(tam_mesa)
	.css("position", "absolute")
	.css("left", $(window).width() / 2 - tam_mesa / 2)
	.css("top", $(window).height() / 2 - tam_mesa / 2);
	
	tam_margem = $("#da").width() * TAMANHO_MARGEM_B;
	$("#db")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	tam_margem = $("#db").width() * TAMANHO_MARGEM_C;
	$("#dc")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	tam_margem = $("#dc").width() * TAMANHO_MARGEM_D;
	$("#dd")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	tam_margem = $("#dd").width() * TAMANHO_MARGEM_E;
	$("#de")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	tam_margem = $("#de").width() * TAMANHO_MARGEM_F;
	$("#df")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	tam_margem = $("#df").width() * TAMANHO_MARGEM_G;
	$("#dg")
	.css("position", "absolute")
	.css("bottom", tam_margem)
	.css("left", tam_margem)
	.css("right", tam_margem)
	.css("top", tam_margem);
	
	/* Definir cores da Mesa */
	$("#da").css("background-color", "maroon");
	$("#db").css("background-color", "green");
	$("#dc").css("background-color", "green");
	//$("#dd").css("background-color", "lightgreen");
	//$("#de").css("background-color", "brown");
	$("#df").css("background-color", "maroon");
	//$("#dg").css("background-color", "yellow");
	
	/* Definir tamanho das Cartas */
	$("object.c")
	.height($("#db").height() * TAMANHO_RELATIVO_CARTA)
	.width($("object.c").height() * DIF_ALTURA_LARGURA_CARTA);
	
	altura_carta = $("object.c").height();
	largura_carta = $("object.c").width();
	
	dif_alt_larg_carta = Math.abs(altura_carta - largura_carta);
	
	/* Definir espaço entre Cartas */
	espaco_entre_cartas = largura_carta * ESPACO_ENTRE_CARTAS;
		
	for (i = 0; i < 4; i++)
		for (j = 0; j < $("#j" + i).children().length; j++)
			$("#j" + i + " > .c" + j)
			.css("position", "absolute")
			.css("left", espaco_entre_cartas * j)
			.css("z-index", j);
	
	/* Definir zona de eventos das Cartas */
	$("div.c")
	.css("position", "absolute")
	.css("bottom", "0px")
	.css("left", "0px")
	.css("right", $("object.c").width() - espaco_entre_cartas)
	.css("top", "0px");
	
	$(".c" + ($("#j0").children().length - 1) + " > div.c")
	.css("right", 0);
	
	/* Posicionar Cartas dos Jogadores */
	tam_zona = $("#dc").width();
	
	tam_mao = largura_carta + espaco_entre_cartas * ($("#j0").children().length - 1);
	$("#j0")
	.css("position", "absolute")
	.css("left", tam_zona / 2 - tam_mao / 2)
	.css("bottom", altura_carta);
	
	tam_mao = largura_carta + espaco_entre_cartas * ($("#j1").children().length - 1);
	$("#j1")
	.css("position", "absolute")
	.css("bottom", tam_zona / 2 - tam_mao / 2)
	.css("right", altura_carta);
	
	tam_mao = largura_carta + espaco_entre_cartas * ($("#j2").children().length - 1);
	$("#j2")
	.css("position", "absolute")
	.css("right", tam_zona / 2 - tam_mao / 2)
	.css("top", altura_carta);
	
	tam_mao = largura_carta + espaco_entre_cartas * ($("#j3").children().length - 1);
	$("#j3")
	.css("position", "absolute")
	.css("top", tam_zona / 2 - tam_mao / 2)
	.css("left", altura_carta);
	
	/* Redimensionar e Posicionar Nome dos Jogadores */
	tam_zona = $("#de").width();
	tam_letra = tam_zona * TAMANHO_LETRA;
	
	$("#j0n")
	.css("font-size", tam_letra)
	.css("position", "absolute")
	.css("left", tam_zona / 2 - $("#j0n").width() / 2)
	.css("bottom", 0)
	.css("font-size", tam_letra);
	
	$("#j1n")
	.css("font-size", tam_letra)
	.css("position", "absolute")
	.css("bottom", tam_zona / 2 - $("#j1n").height() / 2)
	.css("right", $("#j1n").height() / 2 - $("#j1n").width() / 2);
	
	$("#j2n")
	.css("font-size", tam_letra)
	.css("position", "absolute")
	.css("right", tam_zona / 2 - $("#j2n").width() / 2)
	.css("top", 0);
	
	$("#j3n")
	.css("font-size", tam_letra)
	.css("position", "absolute")
	.css("top", tam_zona / 2 - $("#j3n").height() / 2)
	.css("left", $("#j3n").height() / 2 - $("#j3n").width() / 2);
	
	/* Posicionar Cartas no Canto */
	$("#ct")
	.css("position", "absolute")
	.css("left", 0)
	.css("bottom", 0);
	
	$("#e0")
	.css("position", "absolute")
	.css("right", 0)
	.css("bottom", 0);
	
	$("#e1")
	.css("position", "absolute")
	.css("right", dif_alt_larg_carta / 2)
	.css("top", - dif_alt_larg_carta / 2);
	
	$("#texto")
	.css("position", "absolute")
	.css("top", 0)
	.css("left", 0)
	.width(largura_carta);
	
	/* Posicionar Cartas Jogadas */
	tam_zona = $("#dg").width();
	
	$("#j0j")
	.css("position", "absolute")
	.css("left", tam_zona / 2 - largura_carta / 2)
	.css("bottom", 0);
	
	$("#j1j")
	.css("position", "absolute")
	.css("bottom", tam_zona / 2 - altura_carta / 2)
	.css("right", dif_alt_larg_carta / 2);
	
	$("#j2j")
	.css("position", "absolute")
	.css("right", tam_zona / 2 - largura_carta / 2)
	.css("top", 0);
	
	$("#j3j")
	.css("position", "absolute")
	.css("top", tam_zona / 2 - altura_carta / 2)
	.css("left", dif_alt_larg_carta / 2);
}
