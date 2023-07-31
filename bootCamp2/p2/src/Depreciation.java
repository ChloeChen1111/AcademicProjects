import java.util.Scanner;

/**
 * Prints depreciation report for Slime, Weasel, and Swindle.
 *
 * @author Sheila Oh
 * @version 1.0
 */
public class Depreciation {
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
        String assetDesc;       // asset description (for report)
        String prompt;          // prompt
        double beginningValue;  // original asset value in $
        double depreciation;    // annual depreciation in $

        // get the description, beginning value, and depreciation value
        assetDesc = getDescription(keyboard);
        prompt = "What is the original value of the equipment? $";
        beginningValue = getPositiveDouble(keyboard, prompt);
        prompt = "What is the annual depreciation? $";
        depreciation = getPositiveDouble(keyboard, prompt);

        // print asset information and report
        printAssetInfo(assetDesc, beginningValue, depreciation);
        printReport(beginningValue, depreciation);
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
     * Gets a positive, user-input value based on the prompt.
     *
     * @param keyboard   The Scanner object.
     * @param prompt     The string prompt used to prompt for a double input.
     * @return           The positive, double input entered from user.
     */
    public static double getPositiveDouble(Scanner keyboard, String prompt) {
        double value;     // user-input value (constrained to > 0.0)

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
     */
    public static void printReport(double beginningValue, double depreciation) {
        int year = 0;                           // year number (starts at year 1)
        double endOfYearValue = beginningValue; // EOY value of asset in $

        // print column headings
        System.out.println("Year\tDepreciation\tEnd-of-Year Value\t" +
                "Accumulated Depreciation");

        // print report
        while (endOfYearValue > 0.00) {
            if (depreciation > endOfYearValue)
                depreciation = endOfYearValue;
            year++;
            endOfYearValue -= depreciation;

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
        System.out.println("\nHello, this is an asset depreciation reporting" +
                " system.");
    }

    /**
     * Prints the goodbye message.
     */
    public static void goodbye() {
        System.out.println("\nGoodbye and thanks for using Depreciation!\n");
    }
}