class Accounting{
	public  double valueOfSupply;
	public  double vatRate;
	public  double expenseRate;
	public  double getIncome() {
		return valueOfSupply - getExpense();
	}

	public  double getExpense() {
		return valueOfSupply*expenseRate;
	}

	public  double getTotal() {
		return valueOfSupply + getVAT();
	}

	public  double getVAT() {
		return valueOfSupply*vatRate;
	}
	public  void printall(double[] dividendRates,
			double[] dividend) {
		System.out.println("Value of supply : "+valueOfSupply);
		System.out.println("VAT : "+ getVAT());
		System.out.println("Total : "+ getTotal());
		System.out.println("Expense : "+ getExpense());
		System.out.println("Income : "+ getIncome());
		int i = 0;
		while(i < dividendRates.length) {
			System.out.println("Dividend "+Integer.toString(i+1)+" : "+dividend[i]);
			i++;
		}
	}
}
public class AccountingApp {
	
	
	public static void main(String[] args) {
		Accounting a0 = new Accounting();
		a0.vatRate = 0.1;
		a0.valueOfSupply = Double.parseDouble(args[0]);
		a0.expenseRate = 0.3;
		double[] dividendRates = new double[3];
		dividendRates[0] = 0.5;
		dividendRates[1] = 0.3;
		dividendRates[2] = 0.2;
		double[] dividend = new double[3];
		double income = a0.getIncome();
		if(income > 10000.0) {
			dividend[0] = income * dividendRates[0];
			dividend[1] = income * dividendRates[1];
			dividend[2] = income * dividendRates[2];
		} else {
			dividend[0] = income * 1.0;
			dividend[1] = income * 0.0;
			dividend[2] = income * 0.0;
		}
		a0.printall(dividendRates, dividend);
		
		Accounting a1 = new Accounting();
		a1.valueOfSupply = 10000.0;
		a1.vatRate = 0.1;
		a1.expenseRate = 0.3;
		a1.printall(dividendRates, dividend);
		
	}

	

	

}
