import requests

if __name__=="__main__":
    response = requests.get("https://statsapi.web.nhl.com/api/v1/teams").json()

    with open("teamIDs.txt", "w") as f:
        for team in response['teams']:
            f.write('{},{}\n'.format(team['name'], team['id']))

    with open("teamIDs.txt", "r") as f:
        print("teamIDs.txt: ")
        lines = f.readlines()
        for line in lines:
            print(line.strip())


    exit(0)

