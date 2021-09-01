int max (int size1, int size2, int offset);
_Bool between(int pos, int offset, int size);
_Bool equal(int pos, int offset, int size);
_Bool lessThan(int pos1, int pos2,  int size);

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, size2, x_offset);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, size2, y_offset);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    //count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {
      if ((between(x, x_offset, size2) && equal(y, y_offset, size2)) || (between(y, y_offset, size2) && equal(x, x_offset, size2))) {
        printf("*");
      } else if (lessThan(x, y, size1) || lessThan(y, x, size1)) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
      //check if  EITHER
      //    ((x is between x_offset  and x_offset +size2) AND 
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *

      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #

      //else print a space
    //when you finish counting x from 0 to w, 
    //print a newline

}
int max (int size1, int size2, int offset) {
  if (size1 > (size2 + offset)) {
    return size1;
  }
  return size2 + offset;
}
_Bool between (int pos, int offset, int size){
  return pos >= offset && pos < (offset + size);
}
_Bool equal (int pos, int offset, int size) {
  return pos == offset || pos == (offset + size - 1);
}
_Bool lessThan (int pos1, int pos2,  int size) {
  return pos1 < size && (pos2 == 0 || pos2 == size - 1);
}
