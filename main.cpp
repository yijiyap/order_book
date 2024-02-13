#include <iostream>
#include <algorithm>
#include <vector>

class price_level // at each price level, how many orders are there
{
public:
    float price;
    double size;
};

class book // limit order book
{
private:
    std::vector<price_level> bids;
    std::vector<price_level> asks;
public:
    // best bid and ask
    double get_best_bid()
    {
        return 0;
    }
    double get_best_ask()
    {
        return 0;
    }

    // add price level according to the order
    void AddPriceLevel(price_level& pl, bool is_bid)
    {
        if (is_bid)
        {
            bids.push_back(pl); // add price level to bids
            std::sort(bids.begin(), bids.end(), [](auto const& l, auto const& r)
            {
                return l.price > r.price;
            }); // sort bids in descending order
        }
        else
        {
            asks.push_back(pl); // add price level to asks
            std::sort(asks.begin(), asks.end(), [](auto const& l, auto const& r)
            {
                return l.price < r.price;
            }); // sort asks in ascending order
        }
    }

    // delete price level if the price is the same
    void DeletePriceLevel(price_level& pl, bool is_bid)
    {
        if (is_bid)
        {
            bids.erase(std::remove_if(bids.begin(), bids.end(), [&](auto const& l)
            {
                return l.price == pl.price;
            }), bids.end()); // remove price level from bids
        }
        else
        {
            asks.erase(std::remove_if(asks.begin(), asks.end(), [&](auto const& l)
            {
                return l.price == pl.price;
            }), asks.end()); // remove price level from asks
        }
    }
    // method to update price level
    void UpdatePriceLevel(price_level& pl, bool is_bid)
    {
        // find price level
        std::vector<price_level>::iterator it; // what is iterator
        if (is_bid)
        {
            it = std::find_if(bids.begin(), bids.end(), [&](auto const& l)
            {
                return l.price == pl.price;
            }); // find price level in bids
        }
        else
        {
            it = std::find_if(asks.begin(), asks.end(), [&](auto const& l)
            {
                return l.price == pl.price;
            }); // find price level in asks
        }
        if (it != bids.end() || it != asks.end())
        {
            it->price = pl.price; // update price
            it->size = pl.size; // update size
        }
    }
};
