let pessoa = {
	sexoMasc: true,
	peso: 74.6, // atributos do objeto
	altura: 1.30,
	nome: 'Jorge',
	crescer(a = 0) {
		this.altura += a // this é referência ao objeto
	}
}

console.log(`${pessoa.nome} tinha ${pessoa.altura}`)
pessoa.crescer(0.17)
console.log(`E agora tem ${pessoa.altura} metros.`)
