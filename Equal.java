/*Given an array A of integers, find the index of values that satisfy A + B = C + D, where A,B,C & D are integers values in the array

--->
Note:

1) Return the indices `A1 B1 C1 D1`, so that 
  A[A1] + A[B1] = A[C1] + A[D1]
  A1 < B1, C1 < D1
  A1 < C1, B1 != D1, B1 != C1 

2) If there are more than one solutions, 
   then return the tuple of values which are lexicographical smallest. 

Assume we have two solutions
S1 : A1 B1 C1 D1 ( these are values of indices int the array )  
S2 : A2 B2 C2 D2

S1 is lexicographically smaller than S2 iff
  A1 < A2 OR
  A1 = A2 AND B1 < B2 OR
  A1 = A2 AND B1 = B2 AND C1 < C2 OR 
  A1 = A2 AND B1 = B2 AND C1 = C2 AND D1 < D2
Example:

Input: [3, 4, 7, 1, 2, 9, 8]
Output: [0, 2, 3, 5] (O index)
If no solution is possible, return an empty list. */


public class Solution {
    public ArrayList<Integer> equal(ArrayList<Integer> a) {
        ArrayList<Integer> res = null;
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();
        
        for (int i = 0; i < a.size(); i++) {
            for (int j = i+1; j < a.size(); j++) {
                int sum = a.get(i) + a.get(j);
                
                if (map.containsKey(sum)) {
                    ArrayList<Integer> pair = map.get(sum);
                    if (pair.get(0) != i &&
                        pair.get(1) != j &&
                        pair.get(0) != j &&
                        pair.get(1) != i) {
                            ArrayList<Integer> _temp = new ArrayList<>();
                            _temp.add(pair.get(0));
                            _temp.add(pair.get(1));
                            _temp.add(i);
                            _temp.add(j);
                            
                            if (res == null) res = _temp;
                            else {
                                for (int k = 0; k < 4; k++) {
                                    if (res.get(k) < _temp.get(k)){
                                        break;
                                    } else if (res.get(k) > _temp.get(k)) {
                                        res = _temp;
                                        break;
                                    }
                                }
                            }
                            
                        }
                } else {
                    ArrayList<Integer> pair = new ArrayList<>();
                    pair.add(i);
                    pair.add(j);
                    map.put(sum, pair);
                }
            }
        }
        
        return res;
    }
}
