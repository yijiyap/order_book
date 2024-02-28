#include <iostream>
#include <algorithm>
#include <vector>

// at each price level, how many orders are there
class price_level 
{
public:
    float price;
    double size;
};

// limit order book
class book 
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
            /*  
                - `std::remove_if` rearranges the elements in the range `[bid.begin(), bids.end())` such that the elements satisfying the condition are moved to the end of the range.
                - a lambda function is used to determine the condition for the item to be moved.
                - `std::remove_if` returns an iterator pointing to the new logical end of the sequence, where the elements that do not satisfy the condition now reside.
                - The erase function is then called to remove elements from the container. It takes two arguments: the start iterator of the range to remove (returned by std::remove_if), and the real end iterator of the container.
                - So, the second bids.end() is simply providing the real end iterator of the bids container.
            */
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
        if (it != bids.end())
        {
            it->price = pl.price; // update price
            it->size = pl.size; // update size
        }
    }
};

class aggregated_book
{
private:
    std::vector<book> all_books;

public:
    void AddPriceLevel(int venue_id, price_level& pl, bool is_bid)
    {
        all_books[venue_id].AddPriceLevel(pl, is_bid);
    }
    void DeletePriceLevel(int venue_id, price_level& pl, bool is_bid)
    {
        all_books[venue_id].DeletePriceLevel(pl, is_bid);
    }
    void UpdatePriceLevel(int venue_id, price_level& pl, bool is_bid)
    {
        all_books[venue_id].UpdatePriceLevel(pl, is_bid);
    }

    double get_best_bid()
    {
        double best_bid;
        for (book& b : all_books)
        {
            if (best_bid == 0)
                best_bid = b.get_best_bid();
            else
                best_bid = std::max(best_bid, b.get_best_bid());
        }
        return best_bid;
    }

    double get_best_ask()
    {
        double best_ask;
        for (book& b: all_books)
        {
            if (best_ask == 0)
                best_ask = b.get_best_ask();
            else
                best_ask = std::min(best_ask, b.get_best_ask());
        }
        return best_ask;
    }
};

int main()
{
    price_level pl;
    pl.price = 100;
    pl.size = 1000;

    book b;
    b.AddPriceLevel(pl, true);
    b.AddPriceLevel(pl, false);
    b.DeletePriceLevel(pl, true);
    b.UpdatePriceLevel(pl, true);

    aggregated_book ab;
    ab.AddPriceLevel(0, pl, true);
    ab.AddPriceLevel(0, pl, false);
    ab.DeletePriceLevel(0, pl, true);
    ab.UpdatePriceLevel(0, pl, true);
    ab.get_best_bid();
    ab.get_best_ask();

    return 0;
}
