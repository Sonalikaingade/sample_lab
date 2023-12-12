#include <bits/stdc++.h>
using namespace std;

double minsup;
vector<set<string>> datatable;
set<string> products;
map<string, int> freq;
double confidence;

// Splliting the words into single characters inorder to get their count.
vector<string> split(string input)
{
    vector<string> wordList;
    string word = "";
    int ind = 0;

    while (ind < input.size())
    {
        if (isalnum(input[ind]))
        {
            word += input[ind];
        }
        else
        {
            if (!word.empty())
            {
                wordList.push_back(word);
                word = "";
            }
        }
        ind++;
    }

    if (!word.empty())
    {
        wordList.push_back(word);
    }

    return wordList;
}

// Concatenating the strings.
string validateItemset(vector<string> items, int ind)
{
    string result;
    for (int i = 0; i < items.size(); i++)
    {
        if (i != ind)
        {
            result += items[i] + " ";
        }
    }

    // Remove trailing space
    if (!result.empty())
    {
        result.pop_back();
    }

    return result;
}

set<string> copySet(set<string> original)
{
    set<string> duplicate;
    for (auto itr : original)
    {
        duplicate.insert(itr);
    }

    return duplicate;
}

// Generating candidate itemsets for apriori.
set<string> generateCandidateItemsets(set<string> inputItemsets, int itemsetSize)
{
    set<string> candidateItemsets;

    for (auto itr1 = inputItemsets.begin(); itr1 != inputItemsets.end(); itr1++)
    {
        auto itr2 = itr1;
        itr2++;

        for (; itr2 != inputItemsets.end(); itr2++)
        {
            // Split each itemset into individual items.
            vector<string> v1 = split(*itr1);
            vector<string> v2 = split(*itr2);

            bool valid = true;

            // Check if the first (itemsetSize - 1) items of the two itemsets are equal.
            for (int i = 0; i < itemsetSize - 1 and valid; i++)
            {
                if (v1[i] != v2[i])
                {
                    valid = false;
                }
            }

            // Combine the last item from each itemset
            v1.push_back(v2[itemsetSize - 1]);

            // Ensure the items are lexicographically ordered
            if (v1[v1.size() - 1] < v1[v1.size() - 2])
            {
                swap(v1[v1.size() - 1], v1[v1.size() - 2]);
            }

            // Check if all subsets of the combined itemset are in the input set.
            for (int i = 0; i < v1.size() and valid; i++)
            {
                string temp = validateItemset(v1, i);
                if (inputItemsets.find(temp) == inputItemsets.end())
                {
                    valid = false;
                }
            }

            // If all conditions are met
            if (valid)
            {
                candidateItemsets.insert(validateItemset(v1, -1));
            }
        }
    }

    return candidateItemsets;
}

int countOccurrencesOfItems(vector<string> items)
{
    int occurrenceCount = 0;

    // Iterate through the sets in datatable.
    for (set<string> data : datatable)
    {
        bool allPresent = true;

        // Check if all items in 'items' are present in current set.
        for (string item : items)
        {
            if (data.find(item) == data.end())
            {
                allPresent = false;
                break;
            }
        }

        // If all items in items are present in the current set, increment the occurrence count.
        if (allPresent)
        {
            occurrenceCount++;
        }
    }

    return occurrenceCount;
}

ofstream out_file("output.csv");

void generateSubsetsConfidence(vector<string> items, vector<string> subset1, vector<string> subset2, int ind)
{

    if (ind == items.size())
    {
        if (subset1.empty() or subset2.empty())
        {
            return;
        }

        // Simulate calculation of support for the entire set and for subset.
        int count1 = countOccurrencesOfItems(items);
        int count2 = countOccurrencesOfItems(subset1);

        double calculatedConfidence = (((double)count1) / count2) * 100;

        if (calculatedConfidence >= confidence)
        {
            // Write the association rule and confidence to the output file.
            out_file << "{";
            for (string item : subset1)
            {
                out_file << item << " ";
            }
            out_file << "} -> {";
            for (string item : subset2)
            {
                out_file << item << " ";
            }

            out_file << "}, Confidence: " << calculatedConfidence << "%" << endl;
        }
        return;
    }

    subset1.push_back(items[ind]);

    // Recursively explore subsets with the current item in subset1.
    generateSubsetsConfidence(items, subset1, subset2, ind + 1);
    subset1.pop_back();

    subset2.push_back(items[ind]);

    // Reccursively explore subsets with current item in subset2.
    generateSubsetsConfidence(items, subset1, subset2, ind + 1);
    subset2.pop_back();
}

void generateAssociationRules(set<string> freqItems)
{
    for (auto it = freqItems.begin(); it != freqItems.end(); it++)
    {
        vector<string> items = split(*it);
        for (auto itr : items)
            cout << itr << " ";
        cout << endl;
        generateSubsetsConfidence(items, {}, {}, 0);
    }
}

int main()
{
    ifstream file("input1.csv");
    string line;

    if (!file.is_open())
    {
        perror("Error in opening file : ");
        return -1;
    }

    cout << "Enter Support % :";
    cin >> minsup;
    cout << "Enter Confidence % : ";
    cin >> confidence;

    string str;
    while (getline(file, line))
    {
        vector<string> arr = split(line);
        set<string> tmpset;
        for (int i = 0; i < arr.size(); i++)
            tmpset.insert(arr[i]);
        datatable.push_back(tmpset);
        for (set<string>::iterator it = tmpset.begin(); it != tmpset.end(); it++)
        {
            products.insert(*it);
            freq[*it]++;
        }
    }

    file.close();

    int minfre = minsup * datatable.size() / 100;

    queue<set<string>::iterator> q;
    for (set<string>::iterator it = products.begin(); it != products.end(); it++)
    {
        if (freq[*it] < minfre)
        {
            q.push(it);
        }
    }

    while (q.size() > 0)
    {
        products.erase(*q.front());
        q.pop();
    }

    int pass = 1;
    cout << "\nFrequent " << pass++ << " -item set : \n";
    for (set<string>::iterator it = products.begin(); it != products.end(); it++)
    {
        cout << "{" << *it << "} " << freq[*it] * 100 / datatable.size() << "%" << endl;
    }

    int i = 2;
    set<string> prev = copySet(products);
    while (i)
    {
        set<string> cur = generateCandidateItemsets(prev, i - 1);
        if (cur.size() < 1)
        {
            break;
        }

        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
        {
            vector<string> arr = split(*it);
            int tot = 0;

            for (int j = 0; j < datatable.size(); j++)
            {
                bool pres = true;

                for (int k = 0; k < arr.size() && pres; k++)
                {
                    if (datatable[j].find(arr[k]) == datatable[j].end())
                    {
                        pres = false;
                    }
                }
                if (pres)
                    tot++;
            }

            if (tot >= minfre)
                freq[*it] += tot;
            else
                q.push(it);
        }
        while (q.size() > 0)
        {
            cur.erase(*q.front());
            q.pop();
        }

        bool flag = true;
        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
        {
            vector<string> arr = split(*it);
            if (freq[*it] < minfre)
                flag = false;
        }

        if (cur.size() == 0)
            break;

        cout << "\n\nFrequent " << pass++ << " -item set : \n";
        for (set<string>::iterator it = cur.begin(); it != cur.end(); it++)
        {
            cout << "{" << *it << "} " << freq[*it] * 100 / datatable.size() << "%" << endl;
        }

        prev = copySet(cur);
        i++;
    }

    generateAssociationRules(prev);
    return 0;
}