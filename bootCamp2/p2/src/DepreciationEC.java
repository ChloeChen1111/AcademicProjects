import java.util.Scanner;

/**
 * Prints depreciation report for Slime, Weasel, and Swindle.                       
 *
 * @author Sheila Oh                                                                
 * @version 1.0
 */
public class DepreciationEC {
    /**
     * This program welcomes the user, reads in the item (i.e. asset)
     * description, original value, and annual depreciation, and displays the
     * depreciation report. Repeats as requested by the user. A goodbye message
     * is displayed before exiting the program.
     *
     * @param arg  A string array containing the command line arguments.
     */
    public static void main(String[] args) {
        final String YES = "y";    // another report?
        String again = YES;        // holds "y"

        // create Scanner object
        Scanner keyboard = new Scanner(System.in);

        // call welcome
        welcome();

        // call depreciation function
        while (again.toLowerCase().startsWith(YES)) {
            doDepreciation(keyboard);
            System.out.print("\nDo you want to depreciate another item (y/n)? ");
            again = keyboard.nextLine();
        }

        // close Scanner object
        keyboard.close();

        // call goodbye
        goodbye();
    }

    /**
     * Runs the depreciation report for one asset.
     *
     * @param keyboard   The Scanner object.
     */
    public static void doDepreciation(Scanner keyboard) {
        final int STANDARD = 1; // standard report
        String prompt;          // prompt
        String assetDesc;       // asset description (for report)
        double beginningValue;  // original asset value in $
        double depreciation;    // annual depreciation in $
        int numOfYears = 0;     // number of years to fully depreciate
        int reportType;         // holds 1 for standard, 2 for optional

        // ask for standard or optional report
        System.out.print("\nWhich depreciation report would you like to run?\n"
                + "Press 1 for standard, 2 for optional: ");
        reportType = keyboard.nextInt();
        keyboard.nextLine();

        // get asset description and original value
        assetDesc = getDescription(keyboard);
        prompt = "What is the original value of the equipment? $";
        beginningValue = getPositiveDouble(keyboard, prompt);

        // get annual depreciation based on standard or optional report type
        if (reportType == STANDARD) {
            prompt = "What is the annual depreciation? $";
            depreciation = getPositiveDouble(keyboard, prompt);
        } else {
            // get number of years needed to depreciated
            numOfYears = getPositiveInt(keyboard);
            depreciation = beginningValue / numOfYears;
        }

        // print asset information and report
        printAssetInfo(assetDesc, beginningValue, depreciation);
        printReport(beginningValue, depreciation, numOfYears);
    }

    /**
     * Gets the asset description from the user.
     *
     * @param keyboard   The Scanner object.
     * @return           The description of the property.
     */
    public static String getDescription(Scanner keyboard) {
        System.out.print("\nEnter a description of the property: ");
        return keyboard.nextLine();
    }

    /**
     * Gets a positive, double user-input value based on the prompt.
     *
     * @param keyboard   The Scanner object.
     * @param prompt     The string prompt used to prompt for a double input.
     * @return           The positive, double input entered from user.
     */
    public static double getPositiveDouble(Scanner keyboard, String prompt) {
        double value;        // user-input value (constrained to > 0.0)

        // input validation
        do {
            System.out.print(prompt);
            value = keyboard.nextDouble();
        } while (value <= 0.0);

        // consume trailing newline
        keyboard.nextLine();

        // returns input value
        return value;
    }

    /**
     * Gets a positive, integer user-input value based on the prompt.
     *
     * @param keyboard   The Scanner object.
     * @return           The positive, integer input entered from user.
     */
    public static int getPositiveInt(Scanner keyboard) {
        int value;        // user-input value (constrained to > 0)
        String prompt;    // holds prompt

        // input validation
        do {
            prompt = "Enter the number of years it takes the equipment to full "
                    + "depreciate: ";
            System.out.print(prompt);
            value = keyboard.nextInt();
        } while (value <= 0);

        // consume trailing newline
        keyboard.nextLine();

        // returns input value
        return value;
    }

    /**
     * Prints the asset description, beginning value, and depreciation info.
     *
     * @param assetDesc           The equipment description.
     * @param beginningValue      The beginning value.
     * @param annualDepreciation  The annual depreciation.
     */
    public static void printAssetInfo(String assetDesc,
                                      double beginningValue,
                                      double annualDepreciation) {
        System.out.println("\nEquipment description: " + assetDesc);
        System.out.printf("Beginning value: $%.2f\n", beginningValue);
        System.out.printf("Depreciation: $%.2f\n\n", annualDepreciation);
    }

    /**
     * Prints the depreciation report.
     *
     * @param beginningValue      The beginning value.
     * @param annualDepreciation  The annual depreciation.
     * @param numOfYears          The number of years to fully depreciate.
     */
    public static void printReport(double beginningValue,
                                   double depreciation,
                                   int numOfYears) {
        int year = 0;                           // year number (starts at year 1)
        double endOfYearValue = beginningValue; // EOY value of asset in $

        // print column heading
        System.out.println("Year\tDepreciation\tEnd-of-Year Value\t" +
                "Accumulated Depreciation");

        // print report
        while (endOfYearValue > 0.00) {
            if (depreciation > endOfYearValue)
                depreciation = endOfYearValue;
            year++;
            endOfYearValue -= depreciation;

            // if final year, set EOY value equal to 0
            if (year == numOfYears && endOfYearValue > 0.00)
                endOfYearValue = 0.00;

            // print data
            System.out.printf("%2d\t$%,8.2f\t$%,10.2f\t\t$%,10.2f\n",
                    year,
                    depreciation,
                    endOfYearValue,
                    beginningValue - endOfYearValue);
        }
    }

    /**
     * Prints the welcome message.
     */
    public static void welcome() {
        System.out.println("\nWelcome to the asset depreciation reporting system,"
                + " brought to you by Slime, Weasel, and Swindle.");
    }

    /**
     * Prints the goodbye message.
     */
    public static void goodbye() {
        System.out.println("\nGoodbye, and thanks for using the asset "
                + "depreciation reporting system!\n");
    }
} 