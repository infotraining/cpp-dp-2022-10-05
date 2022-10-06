#include "paragraph.hpp"

#include <iostream>

using namespace std;

int main()
{
    // normal paragraph
    shared_ptr<Paragraph> p = make_shared<Paragraph>("Test of paragraph");
    cout << "Normal paragraph: " << p->getHTML() << endl;

    // bolded paragraph
    shared_ptr<Paragraph> bold = make_shared<BoldParagraph>(make_shared<Paragraph>("Test of bold paragraph"));
    cout << "Bolded paragraph: " << bold->getHTML() << endl;

    // bold and italic
    shared_ptr<Paragraph> bold_and_italic = make_shared<ItalicParagraph>(make_shared<BoldParagraph>(make_shared<Paragraph>("Test of italic and bold paragraph")));
    cout << "Bold and italic: " << bold_and_italic->getHTML() << endl;
}
