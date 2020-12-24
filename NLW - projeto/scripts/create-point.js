//  Selecionar estados (UFs)
function populateUFs() {
    const ufSelect = document.querySelector("select[name=uf]")

    fetch("https://servicodados.ibge.gov.br/api/v1/localidades/estados") // Indo à API do IBGE e pegando um array com várias UFs do tipo object
    .then( res => res.json() ) // Arrow function (função com '=>' ) anônima que está retornando o valor pego em formato .json
    .then( states => {

        for(const state of states) /* Para cada estado do conjunto de estados... */ {
            ufSelect.innerHTML += `<option value="${state.id}">${state.nome}</option>` /* (...) serão concatenados novos 'select' com o nome e o "value" iguais às propriedades {nome e id} de cada objeto do vetor */
        }

    } )
}
populateUFs()



//  Selecionar cidades (municípios)
function getCities(event) {
    const citySelect = document.querySelector("select[name=city]")
    const stateInput = document.querySelector("input[name=state]")

    const indexOfSelectedState = event.target.selectedIndex // Obter o id do estado
    stateInput.value = event.target.options[indexOfSelectedState].text // Definir o estado em forma de texto

    const ufValue = event.target.value // Define um valor selecionado

    const url = `https://servicodados.ibge.gov.br/api/v1/localidades/estados/${ufValue}/municipios` // O valor da UF é dinâmico, filtrando assim a quantidade de municípios

    citySelect.innerHTML = '<option value>Selecione a Cidade</option>' // A 'option' do 'select' vem desse modo por padrão
    citySelect.disabled = true // Por padrão, o 'select' vem desabilitado

    fetch(url) // Indo à API do link 'url' e pegando um vetor com vários municípios da UF referente
    .then( res => res.json() )
    .then( cities => {

        for(const city of cities) /* Para cada cidade do conjunto de cidades... */ {
            citySelect.innerHTML += `<option value="${city.nome}">${city.nome}</option>` /* (...)serão concatenados novos 'select' com o nome e o "value" iguais às propriedades {nome e id} de cada objeto do vetor */
        }

        citySelect.disabled = false
    } )
}

document
    .querySelector("select[name=uf]")
    // Ouvidor de eventos, aguardando ser escolhida uma UF para mostrar os municípios
	.addEventListener("change", getCities /* Não se usa os parênteses, para executar a função apenas quando o evento ocorrer */ )


// itens de coleta
const itemsToCollect = document.querySelectorAll(".items-grid li")

for (const item of itemsToCollect){
	item.addEventListener("click", handleSelectedItem)
}

function handleSelectedItem(){
	const itemId = event.target.dataset.id
}