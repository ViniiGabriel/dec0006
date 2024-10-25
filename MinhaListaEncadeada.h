#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
    public:
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada()
    {
        int tam = tamanho();
       for (size_t i = 0; i < tam; tam--)
       {
        removerDoFim();
       }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        if (!vazia())
        {
            return this->_tamanho;
        }
        // substitua a linha abaixo pelo algoritmo esperado
        return 0;
    };

    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return this->_tamanho == 0;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const
    {
        Elemento<T> *dado1 = this->_primeiro;
        int tam = 0;
        int tamanhoLista = tamanho();

        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {

            for (size_t i = 0; i < tamanhoLista; i++)
            {
                if (dado1->dado == dado)
                {
                    return tam;
                }
                dado1 = dado1->proximo;
                tam++;
            }
        }
        throw ExcecaoDadoInexistente();
    };

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.fo
     */
    virtual bool contem(T dado) const
    {
        Elemento<T> *dado1 = this->_primeiro;
        for (std::size_t i = 0; i < tamanho(); i++)
        {
            if (dado1->dado == dado)
            {
                return true;
            }
            dado1 = dado1->proximo;
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        Elemento<T> *dado1 = new Elemento<T>(dado, nullptr);
        dado1->proximo = this->_primeiro;
        this->_primeiro = dado1;
        this->_tamanho++;
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        int tamList = tamanho();

        if (posicao <= tamList)
        {
            if (posicao == 0)
            {
                inserirNoInicio(dado);
            }
            else if (posicao == tamList)
            {
                inserirNoFim(dado);
            }
            else
            {
                Elemento<T> *dadoNovo = new Elemento<T>(dado, nullptr);
                Elemento<T> *dado1 = this->_primeiro;
                for (std::size_t i = 0; i < posicao - 1; i++)
                {
                    dado1 = dado1->proximo;
                }
                dadoNovo->proximo = dado1->proximo;
                dado1->proximo = dadoNovo;
                this->_tamanho++;
            }
        }
        else
        {
            throw ExcecaoPosicaoInvalida();
        }
    };

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        Elemento<T> *dadoNovo = new Elemento<T>(dado, nullptr);
        Elemento<T> *elemLista = this->_primeiro;
        int tam = tamanho();
        if (vazia())
        {
            inserirNoInicio(dado);
            return;
        }
        for (size_t i = 0; i < tam; i++)
        {
            if (i == tamanho() - 1)
            {
                elemLista->proximo = dadoNovo;
                this->_tamanho++;
                return;
            }
            elemLista = elemLista->proximo;
        }
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        Elemento<T> *aux = this->_primeiro;
        T dadoExc = aux->dado;
        this->_primeiro = aux->proximo;
        delete aux;
        this->_tamanho--;

        return dadoExc;
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        int tamList = tamanho();

        if (posicao >= tamList)
        {
            throw ExcecaoPosicaoInvalida();
        }

        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        T dadoExc;

        if (posicao == 0)
        {
            dadoExc = removerDoInicio();
        }
        else if (posicao == tamList - 1)
        {
            dadoExc = removerDoFim();
        }
        else
        {
            Elemento<T> *dado1 = this->_primeiro;
            for (std::size_t i = 0; i < posicao - 1; i++)
            {
                dado1 = dado1->proximo;
            }
            Elemento<T> *aux = dado1->proximo;
            dadoExc = aux->dado;
            dado1->proximo = aux->proximo;
            delete aux;
            this->_tamanho--;
        }

        return dadoExc;
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        Elemento<T> *dado1 = this->_primeiro;
        T dadoExc;

        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if (this->_tamanho == 1)
        {
            dadoExc = removerDoInicio();
            return dadoExc;
        }
        for (std::size_t i = 0; i < tamanho() - 2; i++)
        {
            dado1 = dado1->proximo;
        }

        Elemento<T> *aux = dado1->proximo;
        dadoExc = aux->dado;
        delete aux;
        dado1->proximo = nullptr;

        this->_tamanho--;
        return dadoExc;
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) {

        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        int pos = posicao(dado);
        removerDe(pos);
    };
};

#endif