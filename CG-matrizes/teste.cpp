Questao7(n, pesos[]) {

  livros = ORDENAR(pesos)
  envelopes = 0
  i = 0

  Enquanto (livros.empty != true) {

    se (i = n) {
      livros.remove(n)
      envelopes++
    }

    se ((livros[i] + livros[n]) <= 1) {
      livros.remove(i, n)
      envelopes ++;
      n--;
      i++;
    }

    senão se ((livros[i] + livros[n]) > 1) {
      livros.remove(n)
      envelopes++;
      n--;
    }
    
  }

  retorne envelopes;
}