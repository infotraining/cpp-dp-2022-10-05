#include "report_builder.hpp"
#include "data_parser.hpp"
#include <fstream>
#include <iostream>

using namespace std;

HtmlDocument build_html_document()
{
    HtmlReportBuilder html_builder;

    DataParser parser(html_builder);
    parser.Parse("data.txt");

    return html_builder.get_report();
}

CsvDocument build_csv_document()
{
    CsvReportBuilder csv_builder;

    DataParser parser(csv_builder);
    parser.Parse("data.txt");

    return csv_builder.get_report();
}

int main()
{
    HtmlDocument doc_html = build_html_document();

    cout << doc_html << endl;

    ///////////////////////////////////////////////////////////
    cout << "///////////////////////////////////////////////////////////\n";

    CsvDocument csv_doc = build_csv_document();

    for (const auto& line : csv_doc)
        cout << line << endl;
}
