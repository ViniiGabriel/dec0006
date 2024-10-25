#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL() {
        // escreva o algoritmo esperado
    };

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const
    {
        if (this->raiz == nullptr)
        {
            return true;
        }
        return false;
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const
    {
        if (vazia())
        {
            return 0;
        }
        return quantRecursiva(this->raiz);
    };

    virtual int quantRecursiva(Nodo<T> *nodo) const
    {
        if (nodo == nullptr)
            return 0;

        return 1 + this->quantRecursiva(nodo->filhoEsquerda) + this->quantRecursiva(nodo->filhoDireita);
    };

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const
    {
        Nodo<T> *nodo = this->raiz;

        while (nodo != nullptr && nodo->chave != chave)
        {
            if (nodo->chave < chave)
            {
                nodo = nodo->filhoDireita;
            }
            else
            {
                nodo = nodo->filhoEsquerda;
            }
        }
        return nodo != nullptr;
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        Nodo<T> *nodo = this->raiz;

        while (nodo != nullptr && nodo->chave != chave)
        {
            if (nodo->chave < chave)
            {
                nodo = nodo->filhoDireita;
            }
            else
            {
                nodo = nodo->filhoEsquerda;
            }
        }

        if (nodo != nullptr)
        {
            return nodo->altura;
        }
        else
        {
            return std::nullopt;
        }
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave)
    {
        if (this->raiz == nullptr)
        {
            this->raiz = new Nodo<T>();
            this->raiz->chave = chave;
            this->raiz->altura = 0;
            return;
        }

        inserirRecursivo(this->raiz, chave);

        return;
    };

    virtual void inserirRecursivo(Nodo<T> *nodo, T chave) const
    {
        if (nodo != nullptr)
        {
            if (chave < nodo->chave)
            {
                if (nodo->filhoEsquerda == nullptr)
                {
                    nodo->filhoEsquerda = new Nodo<T>{chave};
                }
                else
                {
                    inserirRecursivo(nodo->filhoEsquerda, chave);
                }
            }
            else
            {
                if (nodo->filhoDireita == nullptr)
                {
                    nodo->filhoDireita = new Nodo<T>{chave};
                }
                else
                {
                    inserirRecursivo(nodo->filhoDireita, chave);
                }
            }

            nodo->altura = 1 + std::max(getAltura(nodo->filhoEsquerda), getAltura(nodo->filhoDireita));
        }
    };

    virtual int getAltura(Nodo<T> *nodo) const
    {
        if (nodo == nullptr)
            return -1;

        else
            // return 1+std::max(getAltura(nodo->filhoEsquerda), getAltura(nodo->filhoDireita));
            return nodo->altura;
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave) {
        // escreva o algoritmo esperado
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        if (!contem(chave))
            return std::nullopt;

        return filhoEsquerdaRecursivo(this->raiz, chave);
    };

    virtual std::optional<T> filhoEsquerdaRecursivo(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr)
            return std::nullopt;

        if (nodo->chave == chave)
        {
            if (nodo->filhoEsquerda == nullptr)
                return std::nullopt;
            else
                return nodo->filhoEsquerda->chave;
        }
        else
        {
            if (chave < nodo->chave)
            {
                return filhoEsquerdaRecursivo(nodo->filhoEsquerda, chave);
            }
            else
            {
                return filhoEsquerdaRecursivo(nodo->filhoDireita, chave);
            }
        }
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        if(!contem(chave))
            return std::nullopt;

        return filhoDireitaRecursivo(this->raiz, chave);
    };

    virtual std::optional<T> filhoDireitaRecursivo(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr)
            return std::nullopt;

        if (nodo->chave == chave)
        {
            if (nodo->filhoDireita == nullptr)
                return std::nullopt;
            else
                return nodo->filhoDireita->chave;
        }
        else
        {
            if (chave < nodo->chave)
            {
                return filhoDireitaRecursivo(nodo->filhoEsquerda, chave);
            }
            else
            {
                return filhoDireitaRecursivo(nodo->filhoDireita, chave);
            }
        }
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        // substitua a linha abaixo pelo algoritmo esperado

        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>;
        emOrdemRecursiva(this->raiz, lista);
        return lista;
    };

    virtual void emOrdemRecursiva(Nodo<T> *nodo, MinhaListaEncadeada<T> *lista) const
    {
        if (nodo != nullptr)
        {
            emOrdemRecursiva(nodo->filhoEsquerda, lista);
            lista->inserirNoFim(nodo->chave);
            emOrdemRecursiva(nodo->filhoDireita, lista);
        }
        return;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        /*
        ListaEncadeada* lista)
         início
         se raiz != NULO então
        adicionaNoFim(lista, raiz->dado);
         Preordem(raiz->filhoEsquerda, 		lista);
         Preordem(raiz->filhoDireita, 	lista);
         fim se
        fim */

        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>;
        preOrdemRecursiva(this->raiz, lista);
        return lista;
    };

    virtual void preOrdemRecursiva(Nodo<T> *nodo, MinhaListaEncadeada<T> *lista) const
    {
        if (nodo != nullptr)
        {
            lista->inserirNoFim(nodo->chave);
            preOrdemRecursiva(nodo->filhoEsquerda, lista);
            preOrdemRecursiva(nodo->filhoDireita, lista);
        }
        return;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        MinhaListaEncadeada<T> *lista = new MinhaListaEncadeada<T>;
        posOrdemRecursiva(this->raiz, lista);
        return lista;
    };

    virtual void posOrdemRecursiva(Nodo<T> *nodo, MinhaListaEncadeada<T> *lista) const
    {
        if (nodo != nullptr)
        {
            posOrdemRecursiva(nodo->filhoEsquerda, lista);
            posOrdemRecursiva(nodo->filhoDireita, lista);
            lista->inserirNoFim(nodo->chave);
        }
        return;
    };
};

#endif