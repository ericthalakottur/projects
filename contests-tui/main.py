import sys
import httpx
import logging

from textual.app import App, ComposeResult
from textual.widgets import Footer, Header, DataTable

class Contests:
    def get_contests(self):
        response = httpx.get("https://codeforces.com/api/contest.list?gym=false")
        if response.status_code == 200:
            logging.info("Retrieved list of contests")
            return response.json()["result"]

        logging.warn("API returned non 200 message")
        return []

    def get_future_contests(self):

        future_contests = filter(lambda contest: contest["phase"] != "FINISHED", self.get_contests())
        contests = []

        for contest in future_contests:
            contests.append((
                contest["name"],
                contest["type"],
                contest["phase"],
                contest["startTimeSeconds"]
            ))

        contests.sort(key=lambda contest: contest[3])
        return contests

class ContestsTUIApplication(App):

    BINDINGS = [("d", "toggle_dark", "Toggle dark mode")]

    def on_load(self) -> None:
        self._contests = Contests()

    def compose(self) -> ComposeResult:
        yield Header()
        yield Footer()
        yield DataTable()

    def action_toggle_dark(self) -> None:
        self.theme = (
            "textual-dark" if self.theme == "textual-light" else "textual-light"
        )

    def on_mount(self) -> None:
        table = self.query_one(DataTable)
        table.add_columns("name", "type", "phase", "startTime")
        future_contests = self._contests.get_future_contests()
        table.add_rows(future_contests)

if __name__ == "__main__":
    logging.basicConfig(stream=sys.stdout, level=logging.INFO)
    print(Contests().get_future_contests())

    app = ContestsTUIApplication()
    app.run()
