#include "library/algoritms/unordered_array.h"

void task_1(){
    unordered_array_set set_A = {(int []) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int []) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int []) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 – 𝐶) Ո (C – A Ս B)
    unordered_array_set res1_1 = unordered_array_set_difference(set_A, set_C);
    unordered_array_set res1_2 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_difference(set_C, res1_2);
    unordered_array_set res1 = unordered_array_set_intersection(res1_1, res1_3);

    //𝐴 Ո 𝐵 Ս ¬𝐴 Ո 𝐶 Ս 𝐵 Ո C
    unordered_array_set res2_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res2_2 = unordered_array_set_intersection(set_A, set_B);
    unordered_array_set res2_3 = unordered_array_set_intersection(res2_1, set_C);
    unordered_array_set res2_4 = unordered_array_set_intersection(set_B, set_C);
    unordered_array_set res2_5 = unordered_array_set_union(res2_2, res2_3);
    unordered_array_set res2 = unordered_array_set_union(res2_5, res2_4);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_1 is identical\n");
    }
}

void task_2(){
    unordered_array_set set_A = {(int []) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int []) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int []) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 – 𝐶) Ո (C – A Ս B)
    unordered_array_set res1_1 = unordered_array_set_difference(set_A, set_C);
    unordered_array_set res1_2 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_difference(set_C, res1_2);
    unordered_array_set res1 = unordered_array_set_intersection(res1_1, res1_3);

    //(𝐴 Ս 𝐵) Ո ((¬𝐴 Ս 𝐵) Ո ¬𝐵 Ս ¬𝐶)
    unordered_array_set res2_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res2_2 = unordered_array_set_complement(set_B, set_U);
    unordered_array_set res2_3 = unordered_array_set_complement(set_C, set_U);
    unordered_array_set res2_4 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res2_5 = unordered_array_set_union(res2_1, set_B);
    unordered_array_set res2_6 = unordered_array_set_intersection(res2_5, res2_2);
    unordered_array_set res2_7 = unordered_array_set_union(res2_6, res2_3);
    unordered_array_set res2 = unordered_array_set_intersection(res2_4, res2_7);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_2 is identical\n");
    }
}

void task_3() {
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 – 𝐶) Ո (C – A Ս B)
    unordered_array_set res1_1 = unordered_array_set_difference(set_A, set_C);
    unordered_array_set res1_2 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_difference(set_C, res1_2);
    unordered_array_set res1 = unordered_array_set_intersection(res1_1, res1_3);

    //𝐶 Δ (𝐴 Ս 𝐵) Δ (𝐶 Ո 𝐴)
    unordered_array_set res2_1 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_3 = unordered_array_set_symmetricDifference(set_C, res2_1);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_3, res2_2);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_3 is identical\n");
    }
}

void task_4() {
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 – 𝐶) Ո (C – A Ս B)
    unordered_array_set res1_1 = unordered_array_set_difference(set_A, set_C);
    unordered_array_set res1_2 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_difference(set_C, res1_2);
    unordered_array_set res1 = unordered_array_set_intersection(res1_1, res1_3);

    //((𝐴 − (𝐴 − 𝐵)) Δ (𝐶 Ո 𝐴) Δ C
    unordered_array_set res2_1 = unordered_array_set_difference(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_difference(set_A, res2_1);
    unordered_array_set res2_3 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_4 = unordered_array_set_symmetricDifference(res2_2, res2_3);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_4, set_C);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_4 is identical\n");
    }
}

void task_5(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //𝐴 Ո 𝐵 Ս ¬𝐴 Ո 𝐶 Ս 𝐵 Ո C
    unordered_array_set res1_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res1_2 = unordered_array_set_intersection(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_intersection(res1_1, set_C);
    unordered_array_set res1_4 = unordered_array_set_intersection(set_B, set_C);
    unordered_array_set res1_5 = unordered_array_set_union(res1_2, res1_3);
    unordered_array_set res1 = unordered_array_set_union(res1_5, res1_4);

    //(𝐴 Ս 𝐵) Ո ((¬𝐴 Ս 𝐵) Ո ¬𝐵 Ս ¬𝐶)
    unordered_array_set res2_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res2_2 = unordered_array_set_complement(set_B, set_U);
    unordered_array_set res2_3 = unordered_array_set_complement(set_C, set_U);
    unordered_array_set res2_4 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res2_5 = unordered_array_set_union(res2_1, set_B);
    unordered_array_set res2_6 = unordered_array_set_intersection(res2_5, res2_2);
    unordered_array_set res2_7 = unordered_array_set_union(res2_6, res2_3);
    unordered_array_set res2 = unordered_array_set_intersection(res2_4, res2_7);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_5 is identical\n");
    }
}

void task_6(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //𝐴 Ո 𝐵 Ս ¬𝐴 Ո 𝐶 Ս 𝐵 Ո C
    unordered_array_set res1_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res1_2 = unordered_array_set_intersection(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_intersection(res1_1, set_C);
    unordered_array_set res1_4 = unordered_array_set_intersection(set_B, set_C);
    unordered_array_set res1_5 = unordered_array_set_union(res1_2, res1_3);
    unordered_array_set res1 = unordered_array_set_union(res1_5, res1_4);

    //𝐶 Δ (𝐴 Ս 𝐵) Δ (𝐶 Ո 𝐴)
    unordered_array_set res2_1 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_3 = unordered_array_set_symmetricDifference(set_C, res2_1);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_3, res2_2);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_6 is identical\n");
    }
}

void task_7(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //𝐴 Ո 𝐵 Ս ¬𝐴 Ո 𝐶 Ս 𝐵 Ո C
    unordered_array_set res1_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res1_2 = unordered_array_set_intersection(set_A, set_B);
    unordered_array_set res1_3 = unordered_array_set_intersection(res1_1, set_C);
    unordered_array_set res1_4 = unordered_array_set_intersection(set_B, set_C);
    unordered_array_set res1_5 = unordered_array_set_union(res1_2, res1_3);
    unordered_array_set res1 = unordered_array_set_union(res1_5, res1_4);

    //((𝐴 − (𝐴 − 𝐵)) Δ (𝐶 Ո 𝐴) Δ C
    unordered_array_set res2_1 = unordered_array_set_difference(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_difference(set_A, res2_1);
    unordered_array_set res2_3 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_4 = unordered_array_set_symmetricDifference(res2_2, res2_3);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_4, set_C);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_7 is identical\n");
    }
}

void task_8(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 Ս 𝐵) Ո ((¬𝐴 Ս 𝐵) Ո ¬𝐵 Ս ¬𝐶)
    unordered_array_set res1_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res1_2 = unordered_array_set_complement(set_B, set_U);
    unordered_array_set res1_3 = unordered_array_set_complement(set_C, set_U);
    unordered_array_set res1_4 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_5 = unordered_array_set_union(res1_1, set_B);
    unordered_array_set res1_6 = unordered_array_set_intersection(res1_5, res1_2);
    unordered_array_set res1_7 = unordered_array_set_union(res1_6, res1_3);
    unordered_array_set res1 = unordered_array_set_intersection(res1_4, res1_7);

    //𝐶 Δ (𝐴 Ս 𝐵) Δ (𝐶 Ո 𝐴)
    unordered_array_set res2_1 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_3 = unordered_array_set_symmetricDifference(set_C, res2_1);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_3, res2_2);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_8 is identical\n");
    }
}

void task_9(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //(𝐴 Ս 𝐵) Ո ((¬𝐴 Ս 𝐵) Ո ¬𝐵 Ս ¬𝐶)
    unordered_array_set res1_1 = unordered_array_set_complement(set_A, set_U);
    unordered_array_set res1_2 = unordered_array_set_complement(set_B, set_U);
    unordered_array_set res1_3 = unordered_array_set_complement(set_C, set_U);
    unordered_array_set res1_4 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_5 = unordered_array_set_union(res1_1, set_B);
    unordered_array_set res1_6 = unordered_array_set_intersection(res1_5, res1_2);
    unordered_array_set res1_7 = unordered_array_set_union(res1_6, res1_3);
    unordered_array_set res1 = unordered_array_set_intersection(res1_4, res1_7);

    //((𝐴 − (𝐴 − 𝐵)) Δ (𝐶 Ո 𝐴) Δ C
    unordered_array_set res2_1 = unordered_array_set_difference(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_difference(set_A, res2_1);
    unordered_array_set res2_3 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_4 = unordered_array_set_symmetricDifference(res2_2, res2_3);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_4, set_C);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_9 is identical\n");
    }
}

void task_10(){
    unordered_array_set set_A = {(int[]) {1, 3, 5, 7}, 4, 4};
    unordered_array_set set_B = {(int[]) {2, 3, 6, 7}, 4, 4};
    unordered_array_set set_C = {(int[]) {4, 5, 6, 7}, 4, 4};
    unordered_array_set set_U = {(int []) {0, 1,2,3,4,5,6,7}, 8, 8};

    //𝐶 Δ (𝐴 Ս 𝐵) Δ (𝐶 Ո 𝐴)
    unordered_array_set res1_1 = unordered_array_set_union(set_A, set_B);
    unordered_array_set res1_2 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res1_3 = unordered_array_set_symmetricDifference(set_C, res1_1);
    unordered_array_set res1 = unordered_array_set_symmetricDifference(res1_3, res1_2);

    //((𝐴 − (𝐴 − 𝐵)) Δ (𝐶 Ո 𝐴) Δ C
    unordered_array_set res2_1 = unordered_array_set_difference(set_A, set_B);
    unordered_array_set res2_2 = unordered_array_set_difference(set_A, res2_1);
    unordered_array_set res2_3 = unordered_array_set_intersection(set_C, set_A);
    unordered_array_set res2_4 = unordered_array_set_symmetricDifference(res2_2, res2_3);
    unordered_array_set res2 = unordered_array_set_symmetricDifference(res2_4, set_C);

    if (unordered_array_set_isEqual(res1, res2)){
        printf("task_10 is identical\n");
    }
}

int mains(){
    task_1();
    task_2();
    task_3();
    task_4();
    task_5();
    task_6();
    task_7();
    task_8();
    task_9();
    task_10();

    return 0;
}