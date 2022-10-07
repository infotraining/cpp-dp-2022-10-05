#include "bitmap.hpp"
#include <algorithm>
#include <array>

using namespace std;

struct Bitmap::BitmapImpl
{
    std::vector<char> image_;

    BitmapImpl(size_t size) : image_(size)
    {}

    BitmapImpl(const BitmapImpl&) = delete;
    BitmapImpl& operator=(const BitmapImpl&) = delete;

    ~BitmapImpl()
    {        
    }
};

Bitmap::Bitmap(size_t size, char fill_char) 
    : pimpl_{ std::make_unique<BitmapImpl>(size) }
{
    fill_n(pimpl_->image_.begin(), pimpl_->image_.size(), fill_char);
}

Bitmap::~Bitmap() = default;

void Bitmap::draw()
{
    cout << "Image: ";
    for (size_t i = 0; i < pimpl_->image_.size(); ++i)
        cout << pimpl_->image_[i];
    cout << endl;
}
