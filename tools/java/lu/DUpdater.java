
public class DUpdater  implements Runnable {
	
	public LUData lu;
	public int x;
	public int y;
	public int b;
	public double tmp[][];
	
	public DUpdater(LUData lu_, int x_, int y_, int b_, double tmp_[][]){
		lu = lu_;
		x = x_;
		y = y_;
		b = b_;
		tmp = tmp_;
	}
	
	public void run(){
		lu.updateD(x, y, b, tmp);
	}

}
