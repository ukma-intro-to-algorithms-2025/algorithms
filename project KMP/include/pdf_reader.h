#ifndef PDF_READER_H
#define PDF_READER_H

typedef struct {
    char **pages;
    int page_count;
} PdfDocument;

PdfDocument *pdf_open_by_name(const char *input_name);

void pdf_free_document(PdfDocument *doc);

#endif