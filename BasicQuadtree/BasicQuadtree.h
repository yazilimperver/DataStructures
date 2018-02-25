/**
 * \file    uQuadtree.h
 * \date    2018/02/07
 * \author  developer
 * \brief   
 */
#ifndef BASICQUADTREE_H__
#define BASICQUADTREE_H__

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <array>
#include <memory>

//! Quadtree icin kullanilacak olan sinirlar
constexpr uint32_t gMaxObjectCount = 5;
constexpr uint32_t gMaxLevelCount  = 5;
    
//! Temel olarak kullanacagimiz quadtree sinifimiz
//! Mevcut quadtree icerisindeki nesneler de sf::FloatRect'tir
class uBasicQuadtree
{
public:
    uBasicQuadtree(int32_t level, const sf::FloatRect& boundary);
        
    //! Recursive olarak butun cocuklari temizler
    void Clear();

    //! Bu metot ile mevcut quadtree node'u dorde bolunur ve her biri icin yeni sinirlar belirlenir
    void Split();

    //! Verilen rectangle' icerisinde barindirabilecek olan cocuk dugumun indeksi. 
    //! Eger herhangi bir cocuk dugume girmez ise -1 donulur ve ebeveyn dugum icerisine yerlestirilir
    int32_t GetIndex(const sf::FloatRect& rect);

    //! Eger eklendikten sonra bu dugum izin verilenden fazla nesne iceriyor ise bolumleme yapilir ve butun cocuklar dagitilir
    void Insert(const sf::FloatRect& rect);

    //! Verilen pRect ile kesisen butun nesneleri don
    void Retrieve(std::vector<sf::FloatRect>& returnedObjects, const sf::FloatRect& pRect);

    //! Verilen indeksi temsil eden cocuk dugum donulur
    uBasicQuadtree* GetChildNode(int32_t index);

    //! Mevcut dugumun sinirlari donulur
    sf::FloatRect GetBoundary() const;

    //! Mevcut dugumun derinligi donulur
    uint32_t GetCurrentLevel() const;

    //! Bu dugumdeki nesneler donulur
    const std::vector<sf::FloatRect>& GetObjects();
protected:
    //! Bu dugumun bulundugu seviye. 0 en ust seviye anlamina gelir
    uint32_t mCurrentLevel = 0;

    //! Bu dugumde tutulan nesneler
    std::vector<sf::FloatRect> mObjects;

    //! Bu dugumun sinirlari
    sf::FloatRect mBoundary;

    //! Cocuk dugumler
    //! 0 => Sag ust, 1 => Sol ust, 2 => Sol alt, 3 => Sag alt
    std::unique_ptr<uBasicQuadtree> mChildNodes[4];
};

#endif // UBASICQUADTREE_H__

