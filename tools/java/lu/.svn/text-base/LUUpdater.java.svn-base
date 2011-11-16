
public class LUUpdater  implements Runnable {

	public LUData lu;
	public int x;
	public int y;
	public double tmp[][];
	
	public LUUpdater(LUData lu_, int x_, int y_, double tmp_[][])
	{
		lu = lu_;
		x = x_;
		y = y_;
		tmp = tmp_;
	}
	                                  
	public void run(){
		lu.updateLU(x, y, tmp);
	}
}
