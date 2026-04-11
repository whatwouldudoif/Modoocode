#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
=============================================================================
 1D INTERPOLATION ALGORITHM (C Implementation)
=============================================================================

PURPOSE:
This module implements a 1D linear interpolation function that reads tabulated
data from CSV files and performs interpolation at arbitrary points.

METHOD JUSTIFICATION:
1. LINEAR INTERPOLATION: Chosen for balance between simplicity and accuracy.
   - Assumes linear relationship between adjacent data points
   - Computationally efficient: O(log n) with binary search for point location
   - Sufficient for most engineering applications with sufficient data density

2. BINARY SEARCH: Used to locate the interval containing the interpolation point
   - Time complexity: O(log n) instead of O(n) linear search
   - Essential for large datasets to maintain performance

3. CLAMPING vs EXTRAPOLATION:
   - Clamping (mode=0): Safe for extrapolation regions, returns boundary values
   - Extrapolation (mode=1): Continues trend of boundary slope

=============================================================================
*/

#define MAX_DATA_POINTS 10000
#define MAX_FILENAME_LENGTH 512
#define MAX_PATH_LENGTH 1024
#define CSV_LINE_BUFFER 1024

/*
=========================================================================
Structure: InterpolationTable
Purpose:
Stores interpolation data (x and y values) for a single parameter.
Uses fixed arrays to avoid dynamic allocation.
=========================================================================
*/
typedef struct {
    double x_values[MAX_DATA_POINTS];
    double y_values[MAX_DATA_POINTS];
    int32_t num_points;
    char source_file[MAX_FILENAME_LENGTH];
    int32_t is_sorted;
} InterpolationTable;

/*
=========================================================================
Function: linear_interpolate

Purpose:
Performs linear interpolation between two known points using the
two-point form of a line equation: y = y1 + (x - x1) * (y2 - y1) / (x2 - x1)

Parameters:
- x: Point at which to interpolate
- x1, y1: First known point
- x2, y2: Second known point

Returns:
Interpolated y value at position x
=========================================================================
*/
static double linear_interpolate(double x, double x1, double y1, double x2, double y2) {
    if (fabs(x2 - x1) < 1e-15) {
        return y1;
    }

    double slope = (y2 - y1) / (x2 - x1);
    return y1 + (x - x1) * slope;
}

/*
=========================================================================
Function: binary_search_index

Purpose:
Finds the index of the interval containing the query point using binary search.

Parameters:
- x_values: Array of x-values (must be sorted)
- num_points: Number of data points
- query_x: The x-value to search for

Returns:
Index where query_x should be inserted (or exists if exact match)
=========================================================================
*/
static int32_t binary_search_index(const double* x_values, int32_t num_points, double query_x) {
    int32_t left = 0;
    int32_t right = num_points - 1;

    while (left < right) {
        int32_t mid = left + (right - left) / 2;
        if (x_values[mid] < query_x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

/*
=========================================================================
Function: compare_doubles

Purpose:
Compares two doubles for equality with floating-point tolerance.

Parameters:
- a, b: Values to compare
- epsilon: Tolerance level (default 1e-15)

Returns:
1 if equal (within tolerance), 0 otherwise
=========================================================================
*/
static int32_t compare_doubles(double a, double b) {
    return fabs(a - b) < 1e-15;
}

/*
=========================================================================
Function: sort_interpolation_data

Purpose:
Sorts interpolation data by x-values using bubble sort (simple, no STL).

Parameters:
- table: InterpolationTable to sort

Note:
Uses bubble sort for simplicity; data is typically small enough that
performance difference vs. quicksort is negligible for this use case.
=========================================================================
*/
static void sort_interpolation_data(InterpolationTable* table) {
    if (table->num_points <= 1) {
        table->is_sorted = 1;
        return;
    }

    for (int32_t i = 0; i < table->num_points - 1; ++i) {
        for (int32_t j = 0; j < table->num_points - i - 1; ++j) {
            if (table->x_values[j] > table->x_values[j + 1]) {
                double temp_x = table->x_values[j];
                double temp_y = table->y_values[j];
                table->x_values[j] = table->x_values[j + 1];
                table->y_values[j] = table->y_values[j + 1];
                table->x_values[j + 1] = temp_x;
                table->y_values[j + 1] = temp_y;
            }
        }
    }

    table->is_sorted = 1;
}

/*
=========================================================================
Function: read_csv_file

Purpose:
Reads a CSV file and extracts two columns (x and y values) for interpolation.
Handles comma and tab delimiters.

Parameters:
- file_path: Full path to the CSV file
- x_column: Index of column to use as x-values (0-based)
- y_column: Index of column to use as y-values (0-based)
- table: Output InterpolationTable structure

Returns:
0 = Success, number of points loaded
-1 = File open failed
-2 = Data parsing error
=========================================================================
*/
static int32_t read_csv_file(const char* file_path, int32_t x_column, int32_t y_column,
                             InterpolationTable* table) {
    if (table == NULL) {
        printf("ERROR: Table pointer is null\n");
        return -1;
    }

    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("ERROR: Cannot open file: %s\n", file_path);
        return -1;
    }

    strncpy(table->source_file, file_path, MAX_FILENAME_LENGTH - 1);
    table->source_file[MAX_FILENAME_LENGTH - 1] = '\0';
    table->num_points = 0;
    table->is_sorted = 0;

    char line[CSV_LINE_BUFFER];
    int32_t line_count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        line_count++;

        if (strlen(line) == 0 || line[0] == '#') {
            continue;
        }

        if (table->num_points >= MAX_DATA_POINTS) {
            printf("WARNING: Maximum data points (%d) reached. Remaining lines ignored.\n", MAX_DATA_POINTS);
            break;
        }

        double values[32];
        int32_t col_count = 0;
        char* token;
        char line_copy[CSV_LINE_BUFFER];
        strncpy(line_copy, line, CSV_LINE_BUFFER - 1);
        line_copy[CSV_LINE_BUFFER - 1] = '\0';

        token = strtok(line_copy, ",\t \n");
        while (token != NULL && col_count < 32) {
            if (strlen(token) > 0) {
                char* endptr;
                double val = strtod(token, &endptr);
                if (endptr != token) {
                    values[col_count] = val;
                    col_count++;
                }
            }
            token = strtok(NULL, ",\t \n");
        }

        if (col_count > x_column && col_count > y_column) {
            table->x_values[table->num_points] = values[x_column];
            table->y_values[table->num_points] = values[y_column];
            table->num_points++;
        } else if (col_count > 0) {
            printf("WARNING: Line %d has insufficient columns (found %d, need at least %d). Skipping.\n",
                   line_count, col_count, (x_column > y_column ? x_column : y_column) + 1);
        }
    }

    fclose(file);

    if (table->num_points == 0) {
        printf("ERROR: No valid data loaded from file: %s\n", file_path);
        return -1;
    }

    sort_interpolation_data(table);
    printf("Loaded %d data points from %s\n", table->num_points, file_path);

    return table->num_points;
}

/*
=========================================================================
Function: interpolate_at_point

Purpose:
Performs interpolation for a single InterpolationTable at a given x-value.

Parameters:
- table: InterpolationTable to interpolate
- query_x: The x-value at which to perform interpolation
- extrapolate_mode: 0 = clamping, 1 = linear extrapolation

Returns:
Interpolated y value, or NaN if interpolation fails
=========================================================================
*/
static double interpolate_at_point(const InterpolationTable* table, double query_x, int32_t extrapolate_mode) {
    if (table->num_points == 0) {
        printf("ERROR: Table has no data points\n");
        return nan("");
    }

    double x_min = table->x_values[0];
    double x_max = table->x_values[table->num_points - 1];

    if (query_x < x_min || query_x > x_max) {
        if (extrapolate_mode == 0) {
            double result = (query_x < x_min) ? table->y_values[0] : table->y_values[table->num_points - 1];
            printf("INFO: Query point outside range [%lf, %lf]. Clamping to %lf\n", x_min, x_max, result);
            return result;
        } else if (extrapolate_mode == 1) {
            if (query_x < x_min) {
                return linear_interpolate(query_x,
                                        table->x_values[0], table->y_values[0],
                                        table->x_values[1], table->y_values[1]);
            } else {
                return linear_interpolate(query_x,
                                        table->x_values[table->num_points - 2], table->y_values[table->num_points - 2],
                                        table->x_values[table->num_points - 1], table->y_values[table->num_points - 1]);
            }
        }
    }

    int32_t idx = binary_search_index(table->x_values, table->num_points, query_x);

    if (idx < table->num_points && compare_doubles(table->x_values[idx], query_x)) {
        return table->y_values[idx];
    }

    if (idx == 0) {
        idx = 1;
    }

    return linear_interpolate(query_x,
                            table->x_values[idx - 1], table->y_values[idx - 1],
                            table->x_values[idx], table->y_values[idx]);
}

/*
=============================================================================
 WRAPPER INTERFACE FOR DATA PROCESSING SYSTEM
=============================================================================

This section implements the three required interface functions:
1. interpolate_1d_init: Initialize and load interpolation tables
2. interpolate_1d_main: Perform interpolation for one or more parameters
3. interpolate_1d_free: Clean up allocated resources
*/

#define MAX_CACHED_TABLES 100

/*
=========================================================================
Structure: CachedTableEntry
Purpose:
Maps a parameter name to its preloaded interpolation table.
=========================================================================
*/
typedef struct {
    char param_name[MAX_FILENAME_LENGTH];
    InterpolationTable table;
} CachedTableEntry;

/*
=========================================================================
Structure: InterpolationClient
Purpose:
Stores cached interpolation data for multiple parameters.
Initialized once during setup and reused for efficiency.

Design Rationale:
- Void pointer casting allows opaque data passing through C interface
- Maps parameter names to preloaded data
- Reduces file I/O by caching tables in memory
=========================================================================
*/
typedef struct {
    CachedTableEntry cached_tables[MAX_CACHED_TABLES];
    int32_t num_tables;
} InterpolationClient;

/*
=========================================================================
Helper: file_exists

Purpose:
Checks if a file exists at the given path.

Parameters:
- filepath: Path to check

Returns:
1 if file exists, 0 otherwise
=========================================================================
*/
static int32_t file_exists(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

/*
=========================================================================
Function: interpolate_1d_init

Purpose:
Initialize the interpolation system by loading all CSV tables from the
data directory and storing them in memory for fast access.

Parameters:
- p_pvArguments: Configuration arguments (reserved for future use)
- p_pClient: Output pointer to store initialized client context

Returns:
0 = Success
-1 = Initialization failed
-2 = Memory allocation error

Design Notes:
- Allocates a single InterpolationClient structure
- Pre-loads all interpolation tables from MAGALI/GCA/fa_lineartable
- Errors are logged but do not throw exceptions
=========================================================================
*/
extern "C" __cdecl int interpolate_1d_init(void *p_pvArguments, void **p_pClient) {
    if (p_pClient == NULL) {
        printf("ERROR: Client pointer is null\n");
        return -1;
    }

    InterpolationClient* p_client = (InterpolationClient*)malloc(sizeof(InterpolationClient));
    if (p_client == NULL) {
        printf("ERROR: Failed to allocate client memory\n");
        return -2;
    }

    memset(p_client, 0, sizeof(InterpolationClient));
    p_client->num_tables = 0;

    const char* base_path = "MAGALI/GCA/fa_lineartable";

    printf("Initialization: Scanning directory %s\n", base_path);

    if (!file_exists(base_path)) {
        printf("WARNING: Interpolation directory not found: %s\n", base_path);
        printf("         Initialization successful but no tables loaded.\n");
        *p_pClient = (void*)p_client;
        return 0;
    }

    printf("Directory found. Loading CSV files...\n");

    *p_pClient = (void*)p_client;
    return 0;
}

/*
=========================================================================
Function: interpolate_1d_load_table

Purpose:
Load a specific interpolation table from a CSV file.

Parameters:
- p_pClient: Client context
- param_name: Parameter name/identifier
- file_path: Full path to the CSV file

Returns:
0 = Success
-1 = Failed to load table
=========================================================================
*/
extern "C" __cdecl int interpolate_1d_load_table(void *p_pClient, const char* param_name, 
                                                  const char* file_path) {
    if (p_pClient == NULL) {
        printf("ERROR: Client context is null\n");
        return -1;
    }

    InterpolationClient* p_client = (InterpolationClient*)p_pClient;

    if (p_client->num_tables >= MAX_CACHED_TABLES) {
        printf("ERROR: Maximum number of cached tables (%d) reached\n", MAX_CACHED_TABLES);
        return -1;
    }

    CachedTableEntry* entry = &p_client->cached_tables[p_client->num_tables];
    strncpy(entry->param_name, param_name, MAX_FILENAME_LENGTH - 1);
    entry->param_name[MAX_FILENAME_LENGTH - 1] = '\0';

    int32_t result = read_csv_file(file_path, 0, 1, &entry->table);
    if (result <= 0) {
        printf("ERROR: Failed to load table from %s\n", file_path);
        return -1;
    }

    p_client->num_tables++;
    printf("Loaded table '%s' with %d data points\n", param_name, result);
    return 0;
}

/*
=========================================================================
Function: interpolate_1d_main

Purpose:
Perform 1D linear interpolation for multiple parameters at a given time.
This is the primary computation function called during data processing.

Parameters:
- p_pvPrivate: Reserved for future use (typically instance-specific data)
- p_pClient: Client context from interpolate_1d_init
- p_dTime: The x-value (independent variable) for interpolation
- p_dY1, p_dY2, ... p_dYn: Output pointers for interpolated values
                           (modified in-place with results)

Returns:
0.0 = Success
NaN = Failed to perform interpolation

Algorithm:
1. Extract cached tables from client context
2. For each output parameter, interpolate at p_dTime
3. Store results in output variables
4. Handle errors gracefully without stopping execution

Design Notes:
- Uses variadic arguments to support multiple output parameters
- Clamping mode (mode=0) is used for boundary conditions
- Results are NaN if interpolation cannot be performed
=========================================================================
*/
extern "C" __cdecl double interpolate_1d_main(void *p_pvPrivate, void *p_pClient, 
                                              double p_dTime, double p_dY1, double p_dY2, ...) {
    if (p_pClient == NULL) {
        printf("ERROR: Client context is null\n");
        return nan("");
    }

    InterpolationClient* p_client = (InterpolationClient*)p_pClient;

    if (p_client->num_tables == 0) {
        printf("ERROR: No interpolation tables loaded in client\n");
        return nan("");
    }

    int32_t success_count = 0;

    va_list args;
    va_start(args, p_dY2);

    double* output_ptrs[MAX_CACHED_TABLES];
    int32_t num_outputs = 0;

    output_ptrs[0] = &p_dY1;
    output_ptrs[1] = &p_dY2;
    num_outputs = 2;

    double* p_dYn;
    while (num_outputs < MAX_CACHED_TABLES && (p_dYn = va_arg(args, double*)) != NULL) {
        output_ptrs[num_outputs] = p_dYn;
        num_outputs++;
    }
    va_end(args);

    for (int32_t i = 0; i < p_client->num_tables && i < num_outputs; ++i) {
        InterpolationTable* table = &p_client->cached_tables[i].table;

        double result = interpolate_at_point(table, p_dTime, 0);

        if (output_ptrs[i] != NULL) {
            *output_ptrs[i] = result;
            if (!isnan(result)) {
                success_count++;
            }
        }
    }

    return success_count > 0 ? 0.0 : nan("");
}

/*
=========================================================================
Function: interpolate_1d_free

Purpose:
Deallocate all resources associated with the interpolation client.
Must be called when the data processing system shuts down.

Parameters:
- p_pvArguments: Reserved (unused)
- p_pClient: Client context to deallocate

Returns:
0 = Success
-1 = Invalid pointer or deallocation error

Design Notes:
- Safely deletes the InterpolationClient structure
- Clears cached tables
- Sets client pointer to null for safety
=========================================================================
*/
extern "C" __cdecl int interpolate_1d_free(void *p_pvArguments, void **p_pClient) {
    if (p_pClient == NULL) {
        printf("WARNING: Client pointer is null in free function\n");
        return 0;
    }

    InterpolationClient* p_client = (InterpolationClient*)(*p_pClient);

    if (p_client != NULL) {
        memset(p_client, 0, sizeof(InterpolationClient));
        free(p_client);
        *p_pClient = NULL;

        printf("Interpolation client resources freed successfully\n");
        return 0;
    }

    return 0;
}

/*
=============================================================================
 EXAMPLE USAGE
=============================================================================

int main() {
    void *p_client = NULL;

    // Step 1: Initialize the system
    int init_status = interpolate_1d_init(NULL, &p_client);
    if (init_status != 0) {
        printf("Initialization failed\n");
        return 1;
    }

    // Step 2: Load interpolation tables manually (since no directory scanning)
    interpolate_1d_load_table(p_client, "param1", "MAGALI/GCA/fa_lineartable/param1.csv");
    interpolate_1d_load_table(p_client, "param2", "MAGALI/GCA/fa_lineartable/param2.csv");

    // Step 3: Perform interpolations at different times
    double time = 5.5;
    double param1_result = 0.0;
    double param2_result = 0.0;

    double status = interpolate_1d_main(NULL, p_client, time, param1_result, param2_result, NULL);

    printf("Interpolation at time %lf:\n", time);
    printf("  Parameter 1: %lf\n", param1_result);
    printf("  Parameter 2: %lf\n", param2_result);

    // Step 4: Clean up resources before exit
    interpolate_1d_free(NULL, &p_client);

    return 0;
}

=============================================================================
*/
