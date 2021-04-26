const Discord = require('discord.js');
const bot = new Discord.Client();
const PREFIX = "maverick!"

var mysql = require('mysql')

var con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "",
    database: "maverick"
  });
  con.connect(err => 
    {
        if(err) 
        {
             console.log("Database connection failed!")
        }
        else 
        {
            console.log(`Database connection successfully!`);
        }
    });
bot.on('ready', () => {
  console.log(`Logged in as ${bot.user.tag}!`);
});

bot.on('message', async message => {

    if(message.author.bot) return;
    let args = message.content.substring(PREFIX.length).split(" ")
    if(UserHasSubscription(message.author.id, (result_have) => {
        if(result_have == true)
        {
            if(!message.member.roles.cache.find(r => r.name === "Active Licence"))
            {
                var role = message.member.guild.roles.cache.find(role => role.name === "Active Licence");
                member.roles.add(role);
            }
        }
        else
        {
            if(message.member.roles.cache.find(r => r.name === "Active Licence"))
            {
                var role = message.guild.roles.cache.get(833442474508812358);
                member.roles.remove(role);
            }            
        }
    }))
    if(message.channel.type == "dm")
    {
        //if(message.content.startsWith(PREFIX)) return
        bot.channels.cache.get('835211737744539689').send(`NEW DM MESSAGE: ${message.author.tag}: ${message.content}`);
    }
    if(message.content.startsWith(`${PREFIX}ping`))
    {
        message.channel.send("Please wait...").then (m => {
            var ping = m.createdTimestamp - message.createdTimestamp;
            var botPing = Math.round(bot.pi)
            let embed = new Discord.MessageEmbed;
            embed.setTitle(":ping_pong: Pong !")
            embed.setColor('FF8000')
            embed.addField("Server latency:", ping+"ms", true)
            embed.addField("Discord API Latency:", bot.ws.ping+"ms", true)
            m.edit('', embed)
        })
    }
    if(message.content.startsWith(`${PREFIX}help`))
    {
        let embed = new Discord.MessageEmbed;
        bot.users.fetch("309333602129281027",false).then(munte => {
            bot.users.fetch("429609867850809344",false).then(seby  => {
                embed.setTitle("Maverick Cheats - Help")
                embed.setDescription(`To purchase acces, you can DM one of the sellers: \
                                    \n${seby.tag} or ${munte.tag}`)
                embed.setFooter("The specified users are the only ones that will sell licences.")
                embed.setColor('FF8000')
                message.channel.send(embed)
            })
        })
    }
    if(message.content.startsWith(`${PREFIX}token`))
    {
        if(UserHasSubscription(message.author.id, (result_have) => {
            if(result_have == true) 
            {
                if(message.channel.type != "dm") return message.reply("\n:flag_ro: Aceasta comanda poate fi utilizata doar in DM-ul botului. \
                                                                    \n:flag_us: This command can only be used in the bot's DM.")
                if(message.channel.type == "dm")
                {
                    var length = 25
                    var result           = [];
                    var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
                    var charactersLength = characters.length;
                    for ( var i = 0; i < length; i++ ) {
                    result.push(characters.charAt(Math.floor(Math.random() * 
                    charactersLength)));
                    }
                    var string = result.join('');
                    message.channel.send(":flag_ro: Acesta este token-ul tau:\
                                        \n:flag_us: This is your token:\
                                        \n`"+string+"`\
                                        \n\n:flag_ro: Recomandam sa stergi acest DM pentru a nu primi interdictie pe un anumit server in urma unei verificari TW.\
                                        \n:flag_us: We recommand to delete this DM to not get banned on a server while a TW verification.")
                    con.query(`UPDATE users SET token = '${string}' WHERE discord_id = '${message.author.id}'`)
                }  
            }
            else return message.reply(":x: | You don't own an active licence.")
        }));
    }
    if(message.content.startsWith(`${PREFIX}createlicence`))
    {
        if(message.author.id != 429609867850809344 && message.author.id != 309333602129281027) return message.reply(":x: | You're missing permissions to use this command.")
        if(!args[1]) return message.channel.send("```Syntax: "+PREFIX+"createlicence [Tagged User/Discord ID] [Duration in days(0 for permanent)]```")
        if(!args[2]) return message.channel.send("```Syntax: "+PREFIX+"createlicence [Tagged User/Discord ID] [Duration in days(0 for permanent)]```")
        var user = message.mentions.users.first() || await bot.users.fetch(args[1]);
        var member = await message.guild.member(user);
        con.query(`SELECT * FROM users WHERE discord_id = '${user.id}'`, function(err, rows) {
            if(rows[0]) return message.reply(":x: | This user already has a subscription.")
            else
            {
                var string;
                var time = Math.round(new Date() / 1000);
                if(args[2] == 0)
                {
                    con.query(`INSERT INTO users(discord_id, hwid, token, subscription_start, subscription_end, last_online) VALUES ('${user.id}', '0', '0', '${time}', '0', 'not found.')`)
                    string = "permanent."
                }
                else con.query(`INSERT INTO users(discord_id, hwid, token, subscription_end, last_online) VALUES ('${user.id}', '0', '0', '${time}', '${time + 86400 * args[2]}', 'not found.')`), string = `${args[2]} zile.`
                message.channel.send(":white_check_mark: | A fost creata o licenta pentru "+user.tag+". Durata: "+string)
            }
        })

    }
    if(message.content.startsWith(`${PREFIX}suspendlicence`))
    {
        if(message.author.id != 429609867850809344 && message.author.id != 309333602129281027) return message.reply(":x: | You're missing permissions to use this command.")
        if(!args[1]) return message.channel.send("```Syntax: "+PREFIX+"suspendlicence [Tagged User/Discord ID] [Reason(optional)]```")
        var user = message.mentions.users.first() || await bot.users.fetch(args[1]);
        var member = await message.guild.member(user);
        con.query(`SELECT * FROM users WHERE discord_id = '${user.id}'`, function(err, rows) {
            if(!rows[0]) return message.reply(":x: | This user already dosen't have a subscription.")
            else
            {
                let reason = 'No reason specified.'
                if (args[2]) reason = args.splice(2).join(" ");
                message.channel.send(":white_check_mark: | Licenta detinuta de "+user.tag+" a fost suspendata de "+message.author.tag+". Motiv: "+reason)
                bot.users.fetch(user.id,false).then(user => {user.send(`Licenta ta pentru Maverick Cheats a fost suspendata de catre ${message.author.tag}. Motiv: ${reason}`)})
                con.query(`DELETE FROM users WHERE discord_id = '${user.id}'`)
            }

        })       
    }
    if(message.content.startsWith(`${PREFIX}mylicence`))
    {
        if(UserHasSubscription(message.author.id, (result_have) => {
          if(result_have == true) {
            con.query(`SELECT * FROM users WHERE discord_id = '${message.author.id}'`, function(err, rows) 
            {
                let embed = new Discord.MessageEmbed;
                var myDate = new Date(rows[0].subscription_end*1000);
                var string = myDate.toUTCString().replace("GMT", "")
                var myDate2 = new Date(rows[0].subscription_start*1000);
                var string2 = myDate2.toUTCString().replace("GMT", "")
                embed.setTitle("Maverick Cheats - Licence for "+message.author.tag)
                embed.setColor('FF8000')
                embed.addField('Subscription date:', string2, true)
                if(rows[0].subscription_end == 0){embed.addField('Subscription end', 'Permanent', true)}else{embed.addField('Subscription end', string, true)}
                message.channel.send(embed)
            })
        }
        else return message.reply(":x: | You don't own an active licence.")
      }));
    }
})
function UserHasSubscription(discord_id, callback)
{
    con.query(`SELECT * FROM users WHERE discord_id = '${discord_id}'`, function(err, rows) {
        if(!rows[0]) return callback(false);
        else if(rows[0]) return callback(true);
    })
}
function GenerateDate()
{
  var ziua = new Date().getDate();
    if(ziua < 10)
    {
      var strziua = "0"+ziua;
    }
    else
    {
      var strziua = ziua;
    }
    var luna = new Date().getMonth() + 1;
    if(luna < 10)
    {
      var strluna = "0"+luna;
    }
    else
    {
      var strluna = luna;
    }
    var an = new Date().getFullYear();
    var ora = new Date().getHours();
    if(ora < 10)
    {
      var strora = "0"+ora;
    }
    else
    {
      var strora = ora;
    }
    var minut = new Date().getMinutes();
    if(minut < 10)
    {
      var strminut = "0"+minut;
    }
    else
    {
      var strminut = minut;
    }
    var secunda = new Date().getSeconds();
    if(secunda < 10)
    {
      var strsecunda = "0"+secunda;
    }
    else
    {
      var strsecunda = secunda;
    }
    return `${strziua}/${strluna}/${an} ${strora}:${strminut}:${strsecunda}`
}

bot.login('ODMzNDQ4MjIwMzE0NTY2Njc4.YHyfJA.1qmi-Z_mvvmdhrd91ExwJbQq6lc');