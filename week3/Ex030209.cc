template<class It> std::size_t max_increasing_len(It p, It q)
{
   unsigned int max = 1; 
   std::size_t counter = 1;
   It i = p;
   ++i;
   for (; i != q; ++i, p++) {
    if (*i > *p) {
        ++counter;
    } else {
      if (counter > max) 
        max = counter;
      counter = 1;
    }
   }
   if (counter > max) 
     max = counter;
   return max;
}