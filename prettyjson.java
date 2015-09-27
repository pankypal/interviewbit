Pretty print a json object using proper indentation.

Every inner brace should increase one indentation to the following lines.
Every close brace should decrease one indentation to the same line and the following lines.
The indents can be increased with an additional ‘\t’
Example 1:

Input : {A:"B",C:{D:"E",F:{G:"H",I:"J"}}}
Output : 
{ 
    A:"B",
    C: 
    { 
        D:"E",
        F: 
        { 
            G:"H",
            I:"J"
        } 
    }     
}
Example 2:

Input : ["foo", {"bar":["baz",null,1.0,2]}]
Output : 
[
    "foo", 
    {
        "bar":
        [
            "baz", 
            null, 
            1.0, 
            2
        ]
    }
]
[] and {} are only acceptable braces in this case.

Assume for this problem that space characters can be done away with.

Your solution should return a list of strings, where each entry corresponds to a single line. The strings should not have “\n” character in them.

public class Solution {
	public ArrayList<String> prettyJSON(String a) {
	    ArrayList<String> res = new ArrayList<String>();
	    int i,j,k;
	    int indent = 0;
	    
	    StringBuilder sb = new StringBuilder();
	    for (i = 0; i < a.length(); i++) {
	        char val = a.charAt(i);
	        
	        if (val == '{'  ||  val == '[') {
	            if (!sb.toString().equals("")) {
    	            sb.insert(0, getIndentedStr(indent));
    	            res.add(sb.toString());
    	            sb.setLength(0);
	            }
	            
	            sb.insert(0, getIndentedStr(indent));
	            sb.append(val);
	            res.add(sb.toString());
	            sb.setLength(0);
	            
	            indent++;
	        } else if (val == '}' || val == ']') {
	            if (!sb.toString().equals("")) {
    	            sb.insert(0, getIndentedStr(indent));
    	            res.add(sb.toString());
    	            sb.setLength(0);
	            }
	            
	            indent--;
	            
	            if ((i+1 < a.length()) && (a.charAt(i+1) == ',')) {
	                sb.insert(0, getIndentedStr(indent));
	                sb.append(val);
	                sb.append(',');
	                i++;
	            } else {
	                sb.insert(0, getIndentedStr(indent));
	                sb.append(val);
	            }
	            
	            res.add(sb.toString());
	            sb.setLength(0);
	        } else if (val == ',') {
	            if (!sb.toString().equals("")) {
    	            sb.insert(0, getIndentedStr(indent));
    	            sb.append(val);
    	            res.add(sb.toString());
    	            sb.setLength(0);
	            }
	        } else {
	            sb.append(val);
	        }
	    }
	    
	    return res;
	}
	
	public String getIndentedStr(int n) {
	    StringBuilder sb = new StringBuilder();
	    
	    if (n <= 0) return "";
	    
	    while (n-- > 0) {
	        sb.append('\t');
	    }
	    
	    return sb.toString();
	}
}
