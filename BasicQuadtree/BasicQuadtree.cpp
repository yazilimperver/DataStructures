#include <BasicQuadtree.h>

BasicQuadtree::BasicQuadtree(int32_t level, const sf::FloatRect& boundary)
{
    mCurrentLevel = level;
    mBoundary = boundary;
}

void BasicQuadtree::Clear()
{
    mObjects.clear();

    for (auto& node : mChildNodes)
    {
        node = nullptr;
    }
}

void BasicQuadtree::Split()
{
    float subWidth = mBoundary.width / 2.0F;
    float subHeight = mBoundary.height / 2.0F;

    float x = mBoundary.left;
    float y = mBoundary.top;

    // Cocuk dugumler icin yer alalim
    mChildNodes[0] = std::make_unique<BasicQuadtree>(mCurrentLevel + 1, sf::FloatRect(x + subWidth, y, subWidth, subHeight));
    mChildNodes[1] = std::make_unique<BasicQuadtree>(mCurrentLevel + 1, sf::FloatRect(x, y, subWidth, subHeight));
    mChildNodes[2] = std::make_unique<BasicQuadtree>(mCurrentLevel + 1, sf::FloatRect(x, y + subHeight, subWidth, subHeight));
    mChildNodes[3] = std::make_unique<BasicQuadtree>(mCurrentLevel + 1, sf::FloatRect(x + subWidth, y + subHeight, subWidth, subHeight));
}

int32_t BasicQuadtree::GetIndex(const sf::FloatRect& rect)
{
    int32_t index = -1;
    float verticalMidpoint = mBoundary.left+ (mBoundary.width / 2);
    float horizontalMidpoint = mBoundary.top + (mBoundary.height / 2);

    // Verilen nesne ust bolumler icerisinde kaliyor mu
    bool topQuadrant = (rect.top < horizontalMidpoint) && ((rect.top + rect.height) < horizontalMidpoint);

    // Verilen nesne alt bolumler icerisinde kaliyor mu
    bool bottomQuadrant = (rect.top > horizontalMidpoint);

    // Verilen nesne sol bolumler icerisinde kaliyor mu
    if ((rect.left< verticalMidpoint)
        &&
        (rect.left+ rect.width < verticalMidpoint))
    {
        if (topQuadrant)
        {
            index = 1;
        }
        else if (bottomQuadrant)
        {
            index = 2;
        }
    }
    // Verilen nesne sag bolumler icerisinde kaliyor mu
    else if (rect.left> verticalMidpoint)
    {
        if (topQuadrant)
        {
            index = 0;
        }
        else if (bottomQuadrant)
        {
            index = 3;
        }
    }

    return index;
}

void BasicQuadtree::Insert(const sf::FloatRect& rect)
{
    if (mChildNodes[0] != nullptr)
    {
        int32_t index = GetIndex(rect);

        // Bu dugum cocuk dugumlere sahip ve bu nesne onlardan ilgili olana eklenecek
        if (index != -1)
        {
            mChildNodes[index]->Insert(rect);

            return;
        }
    }

    // Eger bu nesnenin eklenebilecegi bir cocuk dugum yok ise bu dugume (ebeveyn) dugume ekleyelim
    mObjects.push_back(rect);

    // En alt seviyeye gelmedik fakat bu dugum icin nesne adeti doldu
    if ((mObjects.size() > gMaxObjectCount)
        &&
        (mCurrentLevel < gMaxLevelCount))
    {
        // Eger daha once bu dugum bolunmediyse dorde bolelim
        if (mChildNodes[0] == nullptr)
        {
            Split();
        }

        size_t i = 0;
        while (i < mObjects.size())
        {
            int32_t index = GetIndex(mObjects[i]);

            // Bu nesneyi cocuk dugume ekleyebiliriz
            if (index != -1)
            {
                // Once nesneyi yeni dugume ekleyelim
                mChildNodes[index]->Insert(mObjects[i]);

                // Daha sonra eski dugumden silelim
                mObjects.erase(mObjects.begin() + i);
            }
            // Bu nesneyi cocuk dugume ekleyemiyoruz
            else
            {
                i++;
            }
        }
    }
}

void BasicQuadtree::Retrieve(std::vector<sf::FloatRect>& returnedObjects, const sf::FloatRect& pRect)
{
    int32_t index = GetIndex(pRect);

    if (index != -1 && mChildNodes[0] != nullptr)
    {
        mChildNodes[index]->Retrieve(returnedObjects, pRect);
    }

    returnedObjects.insert(returnedObjects.cend(), mObjects.cbegin(), mObjects.cend());
}

BasicQuadtree* BasicQuadtree::GetChildNode(int32_t index)
{
    BasicQuadtree* node = nullptr;

    if (index < 4)
    {
        node = mChildNodes[index].get();
    }

    return node;
}

sf::FloatRect BasicQuadtree::GetBoundary() const
{
    return mBoundary;
}

uint32_t BasicQuadtree::GetCurrentLevel() const
{
    return mCurrentLevel;
}

const std::vector<sf::FloatRect>& BasicQuadtree::GetObjects()
{
    return mObjects;
}
