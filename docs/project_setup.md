
# To generate a requirements.txt file for a Python project, follow these steps:

# 1. Activate your project's virtual environment (if you are using one).

# 2. Install the pipreqs package using pip. You can do this by running the following command in your terminal:
pip install pipreqs

# 3. Navigate to the root directory of your project in the terminal.

# 4. Run the following command to generate a requirements.txt file:
pipreqs .

# If you want to overwrite an existing requirements.txt file, use the --force option:
pipreqs . --force

# To install the packages listed in the requirements.txt file, run the following command:
pip install -r requirements.txt


-------------------------------------------------------------
# To view all installed Python libraries in a virtual environment, you can activate the virtual environment and then run the following command:
pip list

# list them to a text file
pip freeze > req.txt

# install 
pip install -r req.txt
