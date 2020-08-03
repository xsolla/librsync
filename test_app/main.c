#include <stdio.h>

#include "librsync.h"
#include "fileutil.h"
static size_t block_len = RS_DEFAULT_BLOCK_LEN;
static size_t strong_len = 0;
static int file_force  = 0;

void createSignature(const wchar_t *basicFile, const wchar_t *sigFile)
{
    FILE            *basis_file, *sig_file;
    rs_stats_t      stats;
    rs_result       result;

    basis_file = rs_file_open_ws(basicFile, L"rb", file_force);
    sig_file = rs_file_open_ws(sigFile, L"wb", file_force);

    auto have_error = basis_file == NULL || sig_file == NULL;

    if (have_error) {
        if (basis_file) {
            rs_file_close(basis_file);
        }
        if (sig_file) {
            rs_file_close(sig_file);
        }
        return;
    }

    result = rs_sig_file(basis_file, sig_file, block_len, strong_len,
                         RS_BLAKE2_SIG_MAGIC, &stats);

    rs_file_close(sig_file);
    rs_file_close(basis_file);
    return;
}

void createDelta(const wchar_t *sigFile, const wchar_t *newFile, const wchar_t *deltaFile)
{
    FILE            *sig_file, *new_file, *delta_file;
    rs_result       result;
    rs_signature_t  *sumset;
    rs_stats_t      stats;

    sig_file = rs_file_open_ws(sigFile, L"rb", file_force);
    new_file = rs_file_open_ws(newFile, L"rb", file_force);
    delta_file = rs_file_open_ws(deltaFile, L"wb", file_force);

    auto have_error = sig_file == NULL || new_file == NULL || delta_file == NULL;

    if (have_error) {
        if (delta_file) {
            rs_file_close(delta_file);
        }
        if (new_file) {
            rs_file_close(new_file);
        }
        if (sig_file) {
            rs_file_close(sig_file);
        }
        return;
    }

    result = rs_loadsig_file(sig_file, &sumset, &stats);
    if (result != RS_DONE)
         return;
    if ((result = rs_build_hash_table(sumset)) != RS_DONE)
         return;

    result = rs_delta_file(sumset, new_file, delta_file, &stats);

    rs_file_close(delta_file);
    rs_file_close(new_file);
    rs_file_close(sig_file);

    rs_free_sumset(sumset);

     return;
}

void onCallBac(rs_progress_t *p) {
    printf("EXPECTED %lld, PROCESSED %lld\n", p->expected, p->processed);
}
void applyPatch(const wchar_t *oldFile, const wchar_t *deltaFile, const wchar_t *patchedFile) {
    FILE               *basis_file, *delta_file, *new_file;
    rs_stats_t          stats;
    rs_result           result;
    basis_file = rs_file_open_ws(oldFile, L"rb", file_force);
    delta_file = rs_file_open_ws(deltaFile, L"rb", file_force);
    new_file =   rs_file_open_ws(patchedFile, L"wb", file_force);


    auto have_error = basis_file == NULL || delta_file == NULL || new_file == NULL;

    if (have_error) {
        if (new_file) {
            rs_file_close(new_file);
        }
        if (delta_file) {
            rs_file_close(delta_file);
        }
        if (basis_file) {
            rs_file_close(basis_file);
        }
        return;
    }

    result = rs_patch_file(basis_file, delta_file, new_file, 419522010, &stats, onCallBac, NULL);

    rs_file_close(new_file);
    rs_file_close(delta_file);
    rs_file_close(basis_file);

    return;
}

int main(int argc, char *argv[]) {
    //createSignature(L"C:/Work_files/patchdata/file1_files/file1", L"C:/Work_files/patchdata/file1_files/file1_sig");
    //createDelta(L"C:/Work_files/patchdata/file1_files/file1_sig", L"C:/Work_files/patchdata/file1_files/file1_new", L"C:/Work_files/patchdata/file1_files/file1_delta");
    applyPatch(L"source", L"patch", L"new_file");

    return 0;
}