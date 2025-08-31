#ifndef maxItems
#define maxItems 9
#endif
#ifndef LISTA_HPP
#define LISTA_HPP
template<typename Tipo>
// Estrutura auxiliar para armazenar o item e seu índice original
struct ListaAuxiliar{
	Tipo item = {};
	int indice = 0;
};
template<typename Tipo>
// Estrutura que implementa uma lista simples com tamanho fixo
struct ListaEstatica{
	Tipo items[maxItems] = {};
	int indice = -1;
	ListaAuxiliar<Tipo> itensOrdenado[maxItems] = {};
	// adiciona um item na lista
	bool addItem(Tipo input){
		if((indice+1) >= maxItems)
			return false;
			// throw "voce ta tentando adicionar mais itens que o maximo suportado";

		items[++indice] = input;
		copyItems();
		return true;
	}
	// devolve o item na posicao i
	Tipo getItem(int i){
		if(i >= (indice + 1) || i < 0)
			throw "voce ta consultando fora do range";
		return items[i];
	}
	Tipo operator[](int i){
		return getItem(i);
	}
	// remove o item na posicao i e desloca os elementos posteriores
	bool removeItem(int i) {
		if (i > indice || i < 0)
			return false;
		for (int j = i; j < indice; j++) {
			items[j] = items[j + 1];
		}
		indice--;
		copyItems();
		return true;
	}
	// devolve o indice do item na lista original
	// se nao encontrar retorna -1
	int searchItem(Tipo item){
		int left = 0;
		int right = indice - 1;

		while (left <= right) {
			int mid = (left + right) / 2;
			if (itensOrdenado[mid].item == item) {
				return itensOrdenado[mid].indice; // Retorna o índice na lista original
			} else if (itensOrdenado[mid].item < item) {
				left = mid + 1; // Busca na metade direita
			} else {
				right = mid - 1; // Busca na metade esquerda
			}
		}
		return -1; // Item não encontrado
	}

	ListaEstatica<int> procurarTrios(Tipo item) {
		ListaEstatica<int> indices = {};
		int left = 0;
		int right = indice; 
		int found = -1;

		// Busca binária para encontrar uma ocorrência
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (itensOrdenado[mid].item.valor == item.valor) {
				found = mid;
				break;
			} else if (itensOrdenado[mid].item < item) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}

		if (found == -1)
			return indices; // Não encontrou

		// A partir do item encontrado, expanda para a esquerda para achar o primeiro
		int start = found;
		while (start > 0 && itensOrdenado[start - 1].item == item) {
			start--;
		}

		// A partir do primeiro, colete todos os itens iguais para a direita
		while (start <= indice && itensOrdenado[start].item == item) {
			indices.addItem(itensOrdenado[start].indice);
			start++;
		}
		
		return indices;
	}


	// Copia os itens para o vetor auxiliar e ordena
	void copyItems(){
		for(int i = 0;i < indice+1;i++){
			itensOrdenado[i].item = items[i];
			itensOrdenado[i].indice = i;
		}
		orderItems();
	}
	//ordenando items pelo metodo bubble sort
	// penso em implementar outros metodos de ordenacao depois
	void orderItems(){
		for (int i = 0; i < indice - 1; i++) {
        	// Últimos i elementos já estão ordenados
        	for (int j = 0; j < indice - i - 1; j++) {
        	    // Troca se o elemento atual for maior que o próximo
        	    if (itensOrdenado[j].item > itensOrdenado[j + 1].item) {
        	        // Troca os elementos
        	        ListaAuxiliar<Tipo> temp = itensOrdenado[j];
        	        itensOrdenado[j] = itensOrdenado[j + 1];
        	        itensOrdenado[j + 1] = temp;
        	    }
        	}
   		}
	}
	void printItemsOrdenados(){
		for(int i = 0;i < indice;i++){
			std::cout << "Item: " << itensOrdenado[i].item << ", Indice original: " << itensOrdenado[i].indice << std::endl;
		}
	}
	void printItems(){
		for(int i = 0;i < indice+1;i++){
			std::cout << "Item: " << items[i] << std::endl;
		}
	}
	// Limpa a lista
	void clear(){
		indice = 0;
		for(int i = 0;i < maxItems;i++){
			items[i] = {};
			itensOrdenado[i] = {};
		}
	}
	
};

#endif // LISTA_HPP