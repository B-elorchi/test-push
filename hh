import os
import subprocess

# Replace these URLs with the appropriate ones for your repositories
original_repo_url = "https://github.com/ValetClub/test-001.git"
your_repo_url = "https://github.com/B-elorchi/test-push.git" 

def run_command(command):
    try:
        subprocess.run(command, shell=True, check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error executing command: {e}")
        exit(1)

def sync_repositories():
    if not os.path.exists("test-push"):
        # Clone your repository if not already cloned
        run_command(f"git clone {your_repo_url}")
    os.chdir("test-push")

    # Check if "upstream" remote already exists
    remotes = subprocess.check_output("git remote", shell=True).decode("utf-8").splitlines()
    if "upstream" not in remotes:
        run_command(f"git remote add upstream {original_repo_url}")

    # Fetch the latest changes from the original repository
    run_command("git fetch upstream")

    # Merge the changes from "upstream" into your repository
    run_command("git merge upstream/master")  # Change "master" to the appropriate branch if needed

    # Push the updated repository to your GitHub repository
    run_command("git push origin master")  # Change "master" to the appropriate branch if needed

    print("Sync completed successfully!")

if __name__ == "__main__":
    sync_repositories()
