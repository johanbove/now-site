# TaskWarrior Publish
function task_export () {
    task +ACTIVE project:Plans export > ~/task-active.json
    task +READY project:Plans export > ~/task-ready.json
    task end.after:today-mth project:Plans export > ~/task-completed.json
    theDate=$(date -u +"%Y-%m-%dT%H:%M:%SZ")
    echo "{ \"updated\": \"${theDate}\" }" > ~/task-meta.json
    scp -i $sshkey ~/task-active.json ~/task-ready.json ~/task-completed.json ~/task-meta.json $remote_login:$remote_private_html/now
}
