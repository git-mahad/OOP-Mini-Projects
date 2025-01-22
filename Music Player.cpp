#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> // For file handling
#include <cstdlib>
#include <unistd.h> // For sleep()

using namespace std;

// Song class
class Song {
private:
    string title;
    string artist;
    int duration; // Duration in seconds

public:
    Song(string songTitle = "", string songArtist = "", int songDuration = 0)
        : title(songTitle), artist(songArtist), duration(songDuration) {}

    string getSongTitle() const { return title; }
    string getArtist() const { return artist; }
    int getDuration() const { return duration; }

    void playSong() const {
        cout << "Now Playing: " << title << " by " << artist << endl;
        sleep(duration / 10); // Simulates song playback
    }

    void displaySongDetails() const {
        cout << setw(30) << title << setw(20) << artist << setw(10) << duration << " seconds" << endl;
    }
};

// Playlist class
class Playlist {
private:
    string name;
    vector<Song> songs;

public:
    Playlist(string playlistName = "Default Playlist") : name(playlistName) {}

    string getPlaylistName() const { return name; }

    void addSong(const Song& song) {
        songs.push_back(song);
        cout << "Song \"" << song.getSongTitle() << "\" added to playlist \"" << name << "\".\n";
    }

    void removeSong(const string& songTitle) {
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if (it->getSongTitle() == songTitle) {
                cout << "Song \"" << it->getSongTitle() << "\" removed from playlist \"" << name << "\".\n";
                songs.erase(it);
                return;
            }
        }
        cout << "Song \"" << songTitle << "\" not found in playlist \"" << name << "\".\n";
    }

    void playPlaylist() const {
        if (songs.empty()) {
            cout << "Playlist \"" << name << "\" is empty.\n";
            return;
        }
        cout << "Playing playlist \"" << name << "\":\n";
        for (const auto& song : songs) {
            song.playSong();
        }
        cout << "Finished playing playlist \"" << name << "\".\n";
    }

    void shufflePlay() {
        if (songs.empty()) {
            cout << "Playlist \"" << name << "\" is empty.\n";
            return;
        }
        random_shuffle(songs.begin(), songs.end());
        cout << "Shuffled playlist \"" << name << "\".\n";
        playPlaylist();
    }

    void displayPlaylistDetails() const {
        if (songs.empty()) {
            cout << "Playlist \"" << name << "\" is empty.\n";
            return;
        }
        cout << "Playlist: " << name << "\n";
        cout << setw(30) << "Title" << setw(20) << "Artist" << setw(10) << "Duration\n";
        cout << "---------------------------------------------------------------\n";
        for (const auto& song : songs) {
            song.displaySongDetails();
        }
    }

    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Failed to save playlist to file.\n";
            return;
        }
        outFile << name << endl;
        for (const auto& song : songs) {
            outFile << song.getSongTitle() << "," << song.getArtist() << "," << song.getDuration() << endl;
        }
        outFile.close();
        cout << "Playlist \"" << name << "\" saved to file \"" << filename << "\".\n";
    }

    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Failed to load playlist from file.\n";
            return;
        }
        getline(inFile, name);
        songs.clear();
        string line, title, artist;
        int duration;
        while (getline(inFile, line)) {
            size_t pos1 = line.find(',');
            size_t pos2 = line.rfind(',');
            if (pos1 != string::npos && pos2 != string::npos && pos1 != pos2) {
                title = line.substr(0, pos1);
                artist = line.substr(pos1 + 1, pos2 - pos1 - 1);
                duration = stoi(line.substr(pos2 + 1));
                songs.emplace_back(title, artist, duration);
            }
        }
        inFile.close();
        cout << "Playlist \"" << name << "\" loaded from file \"" << filename << "\".\n";
    }
};

// MusicLibrary class
class MusicLibrary {
private:
    vector<Song> library;

public:
    void addSongToLibrary(const Song& song) {
        library.push_back(song);
        cout << "Song \"" << song.getSongTitle() << "\" added to music library.\n";
    }

    void searchSong(const string& keyword) {
        cout << "Search results for \"" << keyword << "\":\n";
        bool found = false;
        for (const auto& song : library) {
            if (song.getSongTitle().find(keyword) != string::npos ||
                song.getArtist().find(keyword) != string::npos) {
                song.displaySongDetails();
                found = true;
            }
        }
        if (!found) {
            cout << "No songs found for the keyword \"" << keyword << "\".\n";
        }
    }

    const vector<Song>& getLibrary() const { return library; }
};

// Main function
int main() {
    MusicLibrary library;
    Playlist playlist("My Playlist");

    // Prepopulate the music library with some songs
    library.addSongToLibrary(Song("Shape of You", "Ed Sheeran", 240));
    library.addSongToLibrary(Song("Blinding Lights", "The Weeknd", 200));
    library.addSongToLibrary(Song("Believer", "Imagine Dragons", 180));
    library.addSongToLibrary(Song("Someone Like You", "Adele", 210));

    int choice;
    while (true) {
        system("CLS");
        cout << "------ Music Player (Phase 2) ------\n";
        cout << "1. View Library\n";
        cout << "2. Search Song in Library\n";
        cout << "3. Add Song to Playlist\n";
        cout << "4. Remove Song from Playlist\n";
        cout << "5. Display Playlist\n";
        cout << "6. Play Playlist\n";
        cout << "7. Shuffle Play Playlist\n";
        cout << "8. Save Playlist to File\n";
        cout << "9. Load Playlist from File\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            for (const auto& song : library.getLibrary()) {
                song.displaySongDetails();
            }
            sleep(3);
            break;
        case 2: {
            cin.ignore();
            string keyword;
            cout << "Enter song title or artist to search: ";
            getline(cin, keyword);
            library.searchSong(keyword);
            sleep(2);
            break;
        }
        case 3: {
            cin.ignore();
            string title;
            cout << "Enter Song Title to Add to Playlist: ";
            getline(cin, title);

            bool found = false;
            for (const auto& song : library.getLibrary()) {
                if (song.getSongTitle() == title) {
                    playlist.addSong(song);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Song \"" << title << "\" not found in library.\n";
            }
            sleep(2);
            break;
        }
        case 4: {
            cin.ignore();
            string title;
            cout << "Enter Song Title to Remove from Playlist: ";
            getline(cin, title);
            playlist.removeSong(title);
            sleep(2);
            break;
        }
        case 5:
            playlist.displayPlaylistDetails();
            sleep(3);
            break;
        case 6:
            playlist.playPlaylist();
            sleep(3);
            break;
        case 7:
            playlist.shufflePlay();
            sleep(3);
            break;
        case 8: {
            string filename;
            cout << "Enter filename to save playlist: ";
            cin >> filename;
            playlist.saveToFile(filename);
            sleep(2);
            break;
        }
        case 9: {
            string filename;
            cout << "Enter filename to load playlist: ";
            cin >> filename;
            playlist.loadFromFile(filename);
            sleep(2);
            break;
        }
        case 10:
            cout << "Exiting Music Player. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
            sleep(2);
        }
    }

    return 0;
}
