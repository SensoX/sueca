$(document).ready(function () {
	/* JOGO da Sueca*/
	var mesa = new Mesa();
	
	mesa.cb_cartas_dadas = function () {
		$("#e0_nome").html(this.equipas[0].nome + " (" + this.jogadores[0].nome + ", " + this.jogadores[2].nome + ")");
		$("#e1_nome").html(this.equipas[1].nome + " (" + this.jogadores[1].nome + ", " + this.jogadores[3].nome + ")");
		
		$("#e0_pontos").html(this.equipas[0].pontos + " pontos");
		$("#e1_pontos").html(this.equipas[1].pontos + " pontos");
		
		$("#j0_nome").html(this.jogadores[0].nome);
		$("#j1_nome").html(this.jogadores[1].nome);
		$("#j2_nome").html(this.jogadores[2].nome);
		$("#j3_nome").html(this.jogadores[3].nome);
		
		$("#j0_mao").html(this.jogadores[0].mao.toStringCores());
		$("#j1_mao").html(this.jogadores[1].mao.toStringCores());
		$("#j2_mao").html(this.jogadores[2].mao.toStringCores());
		$("#j3_mao").html(this.jogadores[3].mao.toStringCores());
		
		$("#trunfo_carta").html(this.trunfo.toStringCores());
		
		$("#j" + this.primeiro_jogador + "_mesa").attr("bgcolor", "lightblue");
	}
	
	mesa.cb_jogador_jogou = function () {		
		$("#j" + this.jogador + "_mao").html(this.jogadores[this.jogador].mao.toStringCores());
		
		$("#j" + this.jogador + "_mesa").html(this.cartas_jogadas[this.jogador].toStringCores());
	}
	
	mesa.cb_carta_invalida = function () {
		alert("Carta Inválida!");
	}
	
	mesa.cb_baza_terminou = function () {		
		$("#e0_pontos").html(this.equipas[0].pontos + " pontos");
		$("#e1_pontos").html(this.equipas[1].pontos + " pontos");
		
		$("#j0_mesa").html("");
		$("#j1_mesa").html("");
		$("#j2_mesa").html("");
		$("#j3_mesa").html("");
		
		$("#j" + this.primeiro_jogador + "_mesa").removeAttr("bgcolor");
		
		$("#j0_jogado").removeAttr("bgcolor");
		$("#j1_jogado").removeAttr("bgcolor");
		$("#j2_jogado").removeAttr("bgcolor");
		$("#j3_jogado").removeAttr("bgcolor");
		
		$("#j" + this.primeiro_jogador + "_jogado").attr("bgcolor", "lightblue");
		$("#j" + this.vencedor + "_jogado").attr("bgcolor", "lightgreen");
		
		$("#j0_jogado").html(this.cartas_jogadas[0].toStringCores());
		$("#j1_jogado").html(this.cartas_jogadas[1].toStringCores());
		$("#j2_jogado").html(this.cartas_jogadas[2].toStringCores());
		$("#j3_jogado").html(this.cartas_jogadas[3].toStringCores());
		
		$("#j" + this.vencedor + "_mesa").attr("bgcolor", "lightblue");
	}
	
	mesa.cb_jogo_terminou = function () {
		$("#j" + this.vencedor + "_mesa").removeAttr("bgcolor");
		$("#j0_text_carta").attr('readonly', 'readonly');
		
		if (this.vencedora != -1) {
			$("#e" + this.vencedora + "_nome").attr("bgcolor", "lightgreen");
			$("#e" + this.vencedora + "_pontos").attr("bgcolor", "lightgreen");
		} else {
			$("#e0_nome").attr("bgcolor", "yellow");
			$("#e0_pontos").attr("bgcolor", "yellow");
			
			$("#e1_nome").attr("bgcolor", "yellow");
			$("#e1_pontos").attr("bgcolor", "yellow");
		}
	}
	
	mesa.criar_jogadores();
	mesa.criar_equipas();
	mesa.criar_baralho();
	mesa.dar_cartas();
	mesa.jogar();
	
	$("#jogar_carta").submit(function () {
		mesa.jogar($("#j0_text_carta").val());
		
		$("#j0_text_carta").val("");
		$("#j0_text_carta").focus();
		
		return false;
	});
	
	$("#j0_text_carta").keyup(function () {
		if (mesa.is_carta_valida(mesa.jogadores[0].mao.cartas[parseInt($("#j0_text_carta").val())]))
			$("#j0_submit_carta").removeAttr('disabled');
		else
			$("#j0_submit_carta").attr('disabled', 'disable');
	});
	
	$("#j0_text_carta").focus();
});
