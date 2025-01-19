#ifndef SLH_TILEMAP_LOADER_H
#define SLH_TILEMAP_LOADER_H

#include "slh_chars_to_ints.h"

/*
* Read from the given tilemap file and outputs a pointer to an array of integers.
* The map file is assumed to contain comma seperated signed and unsigned integers.
* In case of an error returns NULL.
*/
integer_arr* load_tilemap(const char* input_file) {

	FILE* file_handle = NULL;
	fopen_s(&file_handle, input_file, "rb");
	if (file_handle == NULL) {
		return NULL;
	}

	if (fseek(file_handle, 0, SEEK_END) != 0) {
		fclose(file_handle);
		return NULL;
	}

	fpos_t file_pos;
	if (fgetpos(file_handle, &file_pos) != 0) {
		fclose(file_handle);
		return NULL;
	}

	fseek(file_handle, 0, SEEK_SET);

	unsigned char* map_file_bytes = NULL;
	map_file_bytes = (unsigned char*)malloc(file_pos);
	
	if (map_file_bytes == NULL) {
		fclose(file_handle);
		return NULL;
	}

	memset(map_file_bytes, 0, file_pos);
	map_file_bytes[file_pos] = '\0';

	int bytes_read = fread(map_file_bytes, sizeof(unsigned char), file_pos, file_handle);
	if (bytes_read < file_pos) {
		free(map_file_bytes);
		map_file_bytes = NULL;
		fclose(file_handle);
		return NULL;
	}

	// Determine the number of integers in this map file
	integer_arr* integer_list = chars_to_ints(map_file_bytes, file_pos);
	if (integer_list == NULL) {
		printf("Failed to parse list of integers from file %s\n", input_file);
	}

	fclose(file_handle);

	return integer_list;
}

#endif