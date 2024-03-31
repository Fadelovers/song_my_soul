//github @Fadelovers
func CheckRequests(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()
	username := r.FormValue("username")
	password := r.FormValue("password")

	if username == "heartbeatsheartbeatsheartbeatsheartbeatsheartbeats" && password == "mynamemynamemynamemynamemynamemynamemynamemyname" {
		http.Redirect(w, r, "/main", http.StatusSeeOther)
	} else {
		fmt.Fprintf(w, "wrong username or password")
	}
}
func MainRequests(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "main.html")
}