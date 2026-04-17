#include "../include/pdf_reader.h"
#include <poppler.h>
#include <glib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_DIR "/mnt/c/Users/Acer/OneDrive/Рабочий стол/Pdf Project/"

static PdfDocument *pdf_read_all_pages(const char *filepath) {
    GError *error = NULL;
    char *uri = g_filename_to_uri(filepath, NULL, &error);
    if (!uri) return NULL;

    PopplerDocument *doc = poppler_document_new_from_file(uri, NULL, &error);
    g_free(uri);
    if (!doc) return NULL;

    PdfDocument *pdf = malloc(sizeof(PdfDocument));
    pdf->page_count = poppler_document_get_n_pages(doc);
    pdf->pages = malloc(sizeof(char *) * pdf->page_count);

    for (int i = 0; i < pdf->page_count; i++) {
        PopplerPage *page = poppler_document_get_page(doc, i);
        char *text = poppler_page_get_text(page);
        pdf->pages[i] = text ? g_strdup(text) : g_strdup("");
        if (text) g_free(text);
        g_object_unref(page);
    }
    g_object_unref(doc);
    return pdf;
}
PdfDocument *pdf_open_by_name(const char *input_name) {
    char final_path[2048];

    if (input_name[0] == '/' || (strlen(input_name) > 2 && input_name[1] == ':')) {
        strncpy(final_path, input_name, 2047);
    } else {
        int n = snprintf(final_path, 2048, "%s%s", DEFAULT_DIR, input_name);
        if (strstr(input_name, ".pdf") == NULL && n < 2043) {
            strcat(final_path, ".pdf");
        }
    }

    return pdf_read_all_pages(final_path);
}
void pdf_free_document(PdfDocument *doc) {
    if (!doc) return;
    for (int i = 0; i < doc->page_count; i++) {
        if (doc->pages[i]) g_free(doc->pages[i]);
    }
    free(doc->pages);
    free(doc);
}